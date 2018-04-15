// Copyright 2018 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <QImage>
#include <QMessageBox>
#include "citra_qt/camera/camera_util.h"
#include "citra_qt/camera/opencv_camera.h"
#include "citra_qt/main.h"

namespace Camera {

OpenCVCamera::OpenCVCamera(const std::string& config_) : config(std::move(config_)) {}

OpenCVCamera::~OpenCVCamera() {
    if (capture.isOpened()) {
        capture.release();
    }
}

void OpenCVCamera::StartCapture() {
    if (config.empty()) {
        capture.open(0);
    } else {
        capture.open(config);
    }
}

void OpenCVCamera::StopCapture() {
    capture.release();
}

void OpenCVCamera::SetFormat(Service::CAM::OutputFormat output_format) {
    output_rgb = output_format == Service::CAM::OutputFormat::RGB565;
    if (output_rgb) {
        capture.set(cv::CAP_PROP_CONVERT_RGB, true);
    }
}

constexpr std::array<double, 13> FrameRateList = {
    /* Rate_15 */ 15,
    /* Rate_15_To_5 */ 15,
    /* Rate_15_To_2 */ 15,
    /* Rate_10 */ 10,
    /* Rate_8_5 */ 8.5,
    /* Rate_5 */ 5,
    /* Rate_20 */ 20,
    /* Rate_20_To_5 */ 20,
    /* Rate_30 */ 30,
    /* Rate_30_To_5 */ 30,
    /* Rate_15_To_10 */ 15,
    /* Rate_20_To_10 */ 20,
    /* Rate_30_To_10 */ 30,
};

void OpenCVCamera::SetFrameRate(Service::CAM::FrameRate frame_rate) {
    capture.set(cv::CAP_PROP_FPS, FrameRateList[static_cast<int>(frame_rate)]);
}

void OpenCVCamera::SetResolution(const Service::CAM::Resolution& resolution) {
    width = resolution.width;
    height = resolution.height;
    capture.set(cv::CAP_PROP_FRAME_WIDTH, width);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, height);
}

void OpenCVCamera::SetFlip(Service::CAM::Flip flip) {
    using namespace Service::CAM;
    flip_horizontal = (flip == Flip::Horizontal) || (flip == Flip::Reverse);
    flip_vertical = (flip == Flip::Vertical) || (flip == Flip::Reverse);
}

void OpenCVCamera::SetEffect(Service::CAM::Effect effect) {
    if (effect != Service::CAM::Effect::None) {
        NGLOG_ERROR(Service_CAM, "Unimplemented effect {}", static_cast<int>(effect));
    }
}

std::vector<u16> OpenCVCamera::ReceiveFrame() {
    if (!capture.isOpened()) {
        return std::vector<u16>(width * height);
    }
    capture >> current_frame;
    if (current_frame.empty()) {
        // Reset frame position and retry (for video & image sequence)
        capture.set(cv::CAP_PROP_POS_FRAMES, 0);
        capture >> current_frame;
        if (current_frame.empty()) {
            NGLOG_ERROR(Service_CAM, "Cannot get a frame from camera, returning empty values");
            return std::vector<u16>(width * height);
        }
    }
    return CameraUtil::ProcessImage(CameraUtil::cvMat2QImage(current_frame), width, height,
                                    output_rgb, flip_horizontal, flip_vertical);
}

void OpenCVCamera::OnServicePaused() {
    if (capture.isOpened()) {
        StopCapture();
    }
}

void OpenCVCamera::OnServiceResumed() {
    StartCapture();
}

bool OpenCVCamera::IsPreviewAvailable() {
    StartCapture();
    bool ret = capture.isOpened();
    StopCapture();
    return ret;
}

std::unique_ptr<CameraInterface> OpenCVCameraFactory::Create(const std::string& config) const {
    return std::make_unique<OpenCVCamera>(config);
}

} // namespace Camera
