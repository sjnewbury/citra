// Copyright 2018 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <memory>
#include <QDirIterator>
#include <QFileDialog>
#include <QImageReader>
#include <QMessageBox>
#include <QWidget>
#include "citra_qt/configuration/configure_camera.h"
#include "citra_qt/ui_settings.h"
#include "core/core.h"
#include "core/settings.h"
#include "ui_configure_camera.h"

#ifdef ENABLE_OPENCV_CAMERA
enum class ImageSource {
    Blank,
    StillImage,
    Video, // Video & Image Sequence
    SystemCamera,
};
const std::map<ImageSource, QString> Names = {
    {ImageSource::Blank, QObject::tr("Blank")},
    {ImageSource::StillImage, QObject::tr("Still Image")},
    {ImageSource::Video, QObject::tr("Video & Image Sequence")},
    {ImageSource::SystemCamera, QObject::tr("System Camera")},
};
const std::map<ImageSource, std::vector<QString>> Implementations = {
    {ImageSource::Blank, {"blank"}},
    {ImageSource::StillImage, {"image"}},
    {ImageSource::Video, {"opencv"}},
    {ImageSource::SystemCamera, {"opencv", "qt"}},
};
#else
enum class ImageSource {
    Blank,
    StillImage,
    SystemCamera,
};
const std::map<ImageSource, QString> Names = {
    {ImageSource::Blank, QObject::tr("Blank")},
    {ImageSource::StillImage, QObject::tr("Still Image")},
    {ImageSource::SystemCamera, QObject::tr("System Camera")},
};
const std::map<ImageSource, std::vector<QString>> Implementations = {
    {ImageSource::Blank, {"blank"}},
    {ImageSource::StillImage, {"image"}},
    {ImageSource::SystemCamera, {"qt"}},
};
#endif

enum class ConfigureCamera::CameraPosition { RearRight, Front, RearLeft, RearBoth, Null };

ConfigureCamera::ConfigureCamera(QWidget* parent)
    : QWidget(parent), ui(std::make_unique<Ui::ConfigureCamera>()) {
    ui->setupUi(this);
    camera_name = Settings::values.camera_name;
    camera_config = Settings::values.camera_config;
    current_selected = CameraPosition::Null;
    ui->preview_box->setHidden(true);
    ui->camera_mode->setHidden(true);
    ui->camera_mode_label->setHidden(true);
    ui->camera_position->setHidden(true);
    ui->camera_position_label->setHidden(true);
    for (auto pair : Implementations) {
        if (!pair.second.empty()) {
            ui->image_source->addItem(Names.at(pair.first));
        }
    }
    setConfiguration();
    connectEvents();
}

ConfigureCamera::~ConfigureCamera() {
    stopPreviewing();
}

void ConfigureCamera::connectEvents() {
    connect(ui->image_source,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
            &ConfigureCamera::onImageSourceChanged);
    connect(ui->camera_selection,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [=] {
                CameraPosition pos = getCameraSelection();
                if (pos != CameraPosition::Front) {
                    ui->camera_mode->setCurrentIndex(1);
                    if (camera_name[0] == camera_name[2] && camera_config[0] == camera_config[2]) {
                        ui->camera_mode->setCurrentIndex(0);
                    }
                }
                onCameraChanged();
            });
    connect(ui->camera_mode, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &ConfigureCamera::onCameraChanged);
    connect(ui->camera_position,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
            &ConfigureCamera::onCameraChanged);
    connect(ui->toolButton, &QToolButton::clicked, this, &ConfigureCamera::onToolButtonClicked);
    connect(ui->preview_button, &QPushButton::clicked, this, [=] { startPreviewing(); });
    connect(ui->prompt_before_load, &QCheckBox::stateChanged, this,
            &ConfigureCamera::onPromptBeforeLoadChanged);
}

void ConfigureCamera::setUiDisplay() {
    int camera_selection = getSelectedCameraIndex();
    auto image_source = static_cast<ImageSource>(ui->image_source->currentIndex());
    switch (image_source) {
    case ImageSource::Blank:
    case ImageSource::SystemCamera:
        ui->prompt_before_load->setHidden(true);
        ui->prompt_before_load->setChecked(false);
        ui->camera_file_label->setHidden(true);
        ui->camera_file->setHidden(true);
        ui->camera_file->setText("");
        ui->toolButton->setHidden(true);
        break;
    case ImageSource::StillImage:
        ui->prompt_before_load->setHidden(false);
        ui->camera_file_label->setHidden(false);
        ui->camera_file->setHidden(false);
        ui->toolButton->setHidden(false);
        break;
#ifdef ENABLE_OPENCV_CAMERA
    case ImageSource::Video:
        ui->prompt_before_load->setHidden(true);
        ui->prompt_before_load->setChecked(false);
        ui->camera_file_label->setHidden(false);
        ui->camera_file->setHidden(false);
        ui->toolButton->setHidden(false);
        break;
#endif
    default:
        NGLOG_ERROR(Frontend, "Error: unknown image source");
    }

    // Get the implementations
    ui->implementation->clear();
    for (const auto& implementation :
         Implementations.at(static_cast<ImageSource>(ui->image_source->currentIndex()))) {
        ui->implementation->addItem(implementation);
    }

    ui->implementation->setCurrentText(QString::fromStdString(camera_name[camera_selection]));
    ui->camera_file->setText(QString::fromStdString(camera_config[camera_selection]));
}

void ConfigureCamera::startPreviewing() {
    onCameraChanged(); // Record current setting
    int camera_selection = getSelectedCameraIndex();
    stopPreviewing();
    previewing_camera =
        Camera::CreateCameraPreview(camera_name[camera_selection], camera_config[camera_selection],
                                    preview_width, preview_height);
    if (!previewing_camera) {
        return;
    }
    ui->preview_box->setHidden(false);
    ui->preview_button->setHidden(true);
    preview_width = ui->preview_box->size().width();
    preview_height = preview_width * 0.75;
    ui->preview_box->setToolTip(tr("Resolution: ") + QString::number(preview_width) + "*" +
                                QString::number(preview_height));
    previewing_camera->SetResolution(
        {static_cast<u16>(preview_width), static_cast<u16>(preview_height)});
    previewing_camera->SetEffect(Service::CAM::Effect::None);
    previewing_camera->SetFlip(Service::CAM::Flip::None);
    previewing_camera->SetFormat(Service::CAM::OutputFormat::RGB565);
    previewing_camera->SetFrameRate(Service::CAM::FrameRate::Rate_30);
    previewing_camera->StartCapture();

    timer_id = startTimer(1000 / 30);
}

void ConfigureCamera::stopPreviewing() {
    ui->preview_box->setHidden(true);
    ui->preview_button->setHidden(false);

    if (previewing_camera) {
        previewing_camera->StopCapture();
    }

    if (timer_id != 0) {
        killTimer(timer_id);
        timer_id = 0;
    }
}

void ConfigureCamera::timerEvent(QTimerEvent* event) {
    if (event->timerId() != timer_id) {
        return;
    }
    if (!previewing_camera) {
        killTimer(timer_id);
        timer_id = 0;
        return;
    }
    std::vector<u16> frame = previewing_camera->ReceiveFrame();
    int width = ui->preview_box->size().width();
    int height = width * 0.75;
    if (width != preview_width || height != preview_height) {
        stopPreviewing();
        return;
    }
    QImage image(width, height, QImage::Format::Format_RGB16);
    std::memcpy(image.bits(), frame.data(), width * height * sizeof(u16));
    ui->preview_box->setPixmap(QPixmap::fromImage(image));
}

void ConfigureCamera::onImageSourceChanged(int index) {
    stopPreviewing();
    setUiDisplay();
}

void ConfigureCamera::onToolButtonClicked() {
    int camera_selection = getSelectedCameraIndex();
    QString filter;
    if (camera_name[camera_selection] == "image") {
        QList<QByteArray> types = QImageReader::supportedImageFormats();
        QList<QString> temp_filters;
        for (const QByteArray& type : types) {
            temp_filters << QString("*." + QString(type));
        }
        filter = tr("Supported image files (%1)").arg(temp_filters.join(" "));
    }
#ifdef ENABLE_OPENCV_CAMERA
    else if (camera_name[camera_selection] == "opencv") {
        filter = tr("Supported video files (*.mpg *.avi)");
    }
#endif
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", filter);
    if (!path.isEmpty()) {
        ui->camera_file->setText(path);
    }
}

void ConfigureCamera::onPromptBeforeLoadChanged(int state) {
    if (state == Qt::Checked) {
        ui->camera_file->setText("");
        ui->camera_file->setDisabled(true);
        ui->toolButton->setDisabled(true);
    } else {
        ui->camera_file->setDisabled(false);
        ui->toolButton->setDisabled(false);
    }
}

void ConfigureCamera::setConfiguration() {
    int index = getSelectedCameraIndex();
    // Convert camera name to image sources
    if (camera_name[index] == "blank") {
        ui->image_source->setCurrentText(tr("Blank"));
    } else if (camera_name[index] == "image") {
        ui->image_source->setCurrentText(tr("Still Image"));
        if (camera_config[index].empty()) {
            ui->prompt_before_load->setChecked(true);
        }
    }
#ifdef ENABLE_OPENCV_CAMERA
    else if (camera_name[index] == "opencv") {
        if (camera_config[index].empty()) {
            ui->image_source->setCurrentText(tr("System Camera"));
        } else {
            ui->image_source->setCurrentText(tr("Video & Image Sequence"));
        }
    }
#endif
    else if (camera_name[index] == "qt") {
        ui->image_source->setCurrentText(tr("System Camera"));
    } else {
        NGLOG_ERROR(Frontend, "Unknown camera type {}", camera_name[index].c_str());
        QString message =
            tr(("Sorry, but your configuration file seems to be invalid:\n\nUnknown camera type " +
                camera_name[index])
                   .c_str());
#ifndef ENABLE_OPENCV_CAMERA
        if (camera_name[index] == "opencv") {
            message.append(tr("\n\nNote: This build does not have the OpenCV camera included."));
        }
#endif
        QMessageBox::critical(this, tr("Error"), message);
        ui->image_source->setCurrentText(tr("Blank"));
    }

    setUiDisplay();
}

void ConfigureCamera::applyConfiguration() {
    onCameraChanged(); // Record current data
    stopPreviewing();
    Settings::values.camera_name = camera_name;
    Settings::values.camera_config = camera_config;
    Settings::Apply();
}

void ConfigureCamera::onCameraChanged() {
    CameraPosition pos = getCameraSelection();
    if (current_selected == CameraPosition::RearBoth) {
        camera_name[0] = ui->implementation->currentText().toStdString();
        camera_config[0] = ui->camera_file->text().toStdString();
        camera_name[2] = ui->implementation->currentText().toStdString();
        camera_config[2] = ui->camera_file->text().toStdString();
    } else if (current_selected != CameraPosition::Null) {
        int camera_selection = static_cast<int>(current_selected);
        camera_name[camera_selection] = ui->implementation->currentText().toStdString();
        camera_config[camera_selection] = ui->camera_file->text().toStdString();
    }
    if (pos == CameraPosition::RearBoth) {
        ui->camera_position->setHidden(true);
        ui->camera_position_label->setHidden(true);
        ui->camera_mode->setHidden(false);
        ui->camera_mode_label->setHidden(false);
    } else {
        int camera_id = static_cast<int>(pos);
        ui->camera_position->setHidden(pos == CameraPosition::Front);
        ui->camera_position_label->setHidden(pos == CameraPosition::Front);
        ui->camera_mode->setHidden(pos == CameraPosition::Front);
        ui->camera_mode_label->setHidden(pos == CameraPosition::Front);
    }
    current_selected = pos;
    stopPreviewing();
    setConfiguration();
}

ConfigureCamera::CameraPosition ConfigureCamera::getCameraSelection() {
    switch (ui->camera_selection->currentIndex()) {
    case 0: // Front
        return CameraPosition::Front;
    case 1: // Rear
        if (ui->camera_mode->currentIndex() == 0) {
            // Single (2D) mode
            return CameraPosition::RearBoth;
        } else {
            // Double (3D) mode
            return (ui->camera_position->currentIndex() == 0) ? CameraPosition::RearLeft
                                                              : CameraPosition::RearRight;
        }
    default:
        NGLOG_ERROR(Frontend, "Unknown camera selection");
        return CameraPosition::Front;
    }
}

int ConfigureCamera::getSelectedCameraIndex() {
    CameraPosition pos = getCameraSelection();
    int camera_selection = static_cast<int>(pos);
    if (pos == CameraPosition::RearBoth) { // Single Mode
        camera_selection = 0;              // Either camera is the same, so we return RearRight
    }
    return camera_selection;
}

void ConfigureCamera::retranslateUi() {
    ui->retranslateUi(this);
}
