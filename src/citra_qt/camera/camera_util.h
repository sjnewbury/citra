// Copyright 2018 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <vector>
#include "common/common_types.h"

namespace cv {
class Mat;
}
class QImage;

namespace CameraUtil {

/// Converts QImage to a yuv formatted std::vector
std::vector<u16> Rgb2Yuv(const QImage& source, int width, int height);

/// Processes the QImage (resizing, flipping ...) and converts it to a std::vector
std::vector<u16> ProcessImage(const QImage& source, int width, int height, bool output_rgb,
                              bool flip_horizontal, bool flip_vertical);

#ifdef ENABLE_OPENCV_CAMERA
/// Converts cv::Mat to a std::vector
QImage cvMat2QImage(const cv::Mat& mat);
#endif

} // namespace CameraUtil
