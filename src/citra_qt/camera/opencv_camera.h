// Copyright 2018 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include "citra_qt/camera/qt_camera_factory.h"
#include "core/frontend/camera/interface.h"

namespace Camera {
class OpenCVCamera final : public CameraInterface {
public:
    explicit OpenCVCamera(const std::string& config);
    ~OpenCVCamera();
    void StartCapture() override;
    void StopCapture() override;
    void SetResolution(const Service::CAM::Resolution&) override;
    void SetFlip(Service::CAM::Flip) override;
    void SetEffect(Service::CAM::Effect) override;
    void SetFormat(Service::CAM::OutputFormat) override;
    void SetFrameRate(Service::CAM::FrameRate frame_rate) override;
    std::vector<u16> ReceiveFrame() override;
    void OnServicePaused() override;
    void OnServiceResumed() override;
    bool IsPreviewAvailable() override;

private:
    cv::VideoCapture capture;
    const std::string config;
    cv::Mat current_frame;
    int width, height;
    bool output_rgb;
    bool flip_horizontal, flip_vertical;
};

class OpenCVCameraFactory final : public QtCameraFactory {
public:
    std::unique_ptr<CameraInterface> Create(const std::string& config) const override;
};

} // namespace Camera
