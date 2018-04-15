// Copyright 2018 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/frontend/camera/factory.h"
#include "core/frontend/camera/interface.h"

namespace Ui {
class ConfigureCamera;
}

class ConfigureCamera : public QWidget {
    Q_OBJECT

public:
    explicit ConfigureCamera(QWidget* parent = nullptr);
    ~ConfigureCamera();

    void applyConfiguration();
    void retranslateUi();

    void timerEvent(QTimerEvent*) override;

public slots:
    void onCameraChanged();
    void onImageSourceChanged(int index);
    void onToolButtonClicked();
    void onPromptBeforeLoadChanged(int state);

private:
    enum class CameraPosition;
    void setConfiguration();
    void setUiDisplay();
    void startPreviewing();
    void stopPreviewing();
    void connectEvents();
    CameraPosition getCameraSelection();
    int getSelectedCameraIndex();

private:
    std::unique_ptr<Ui::ConfigureCamera> ui;
    std::array<std::string, 3> camera_name;
    std::array<std::string, 3> camera_config;
    int timer_id = 0;
    int preview_width = 0;
    int preview_height = 0;
    CameraPosition current_selected;
    bool is_previewing = false;
    std::unique_ptr<Camera::CameraInterface> previewing_camera;
};
