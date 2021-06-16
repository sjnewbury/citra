// Copyright 2017 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <glad/glad.h>

#include "core/settings.h"
#include "core/3ds.h"
#include "common/logging/log.h"
#include "libretro.h"
#include "citra_libretro.h"
#include "environment.h"

/// LibRetro expects a "default" GL state.
void ResetGLState() {
    // Clean up state.

    glLogicOp(GL_COPY);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

    glDisable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 0, 0xFFFFFFFF);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ZERO);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFuncSeparate(GL_ONE, GL_ZERO, GL_ONE, GL_ZERO);
    glBlendColor(0, 0, 0, 0);

    glDisable(GL_COLOR_LOGIC_OP);

    glDisable(GL_DITHER);

    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    //glUseProgram(0);
    glActiveTexture(GL_TEXTURE0);
}

EmuWindow_LibRetro::EmuWindow_LibRetro() {}

EmuWindow_LibRetro::~EmuWindow_LibRetro() {}

void EmuWindow_LibRetro::SwapBuffers() {
    submittedFrame = true;

    ResetGLState();
    glUseProgram(0);
    LibRetro::UploadVideoFrame(RETRO_HW_FRAME_BUFFER_VALID,
                               static_cast<unsigned>(width), static_cast<unsigned>(height), 0);
    glUseProgram(0);
    ResetGLState();
}

void EmuWindow_LibRetro::SetupFramebuffer() {
    ResetGLState();
    glBindFramebuffer(GL_FRAMEBUFFER, static_cast<GLuint>(LibRetro::GetFramebuffer()));
}

void EmuWindow_LibRetro::PollEvents() {
    LibRetro::PollInput();
}

void EmuWindow_LibRetro::MakeCurrent() {
    // They don't get any say in the matter - GL context is always current!
}

void EmuWindow_LibRetro::DoneCurrent() {
    // They don't get any say in the matter - GL context is always current!
}

void EmuWindow_LibRetro::OnMinimalClientAreaChangeRequest(const std::pair<unsigned, unsigned> &minimal_size) {
    width = minimal_size.first;
    height = minimal_size.second;
}

void EmuWindow_LibRetro::Prepare(bool hasOGL) {
    // TODO: Handle custom layouts
    int baseX;
    int baseY;

    float scaling = Settings::values.resolution_factor;

    bool swapped = Settings::values.swap_screen;

    switch(Settings::values.layout_option) {
        case Settings::LayoutOption::SingleScreen:
            if (swapped) {
                baseX = Core::kScreenBottomWidth;
                baseY = Core::kScreenBottomHeight;
            } else {
                baseX = Core::kScreenTopWidth;
                baseY = Core::kScreenTopHeight;
            }
            baseX *= scaling;
            baseY *= scaling;
            break;
        case Settings::LayoutOption::LargeScreen:
            if (swapped) {
                baseX = Core::kScreenBottomWidth + Core::kScreenTopWidth / 4;
                baseY = Core::kScreenBottomHeight;
            } else {
                baseX = Core::kScreenTopWidth + Core::kScreenBottomWidth / 4;
                baseY = Core::kScreenTopHeight;
            }

            if (scaling < 4) {
                // Unfortunately, to get this aspect ratio correct (and have non-blurry 1x scaling),
                //  we have to have a pretty large buffer for the minimum ratio.
                baseX *= 4;
                baseY *= 4;
            } else {
                baseX *= scaling;
                baseY *= scaling;
            }
            break;
        case Settings::LayoutOption::Default:
        default:
            if (swapped) {
                baseX = Core::kScreenBottomWidth;
            } else {
                baseX = Core::kScreenTopWidth;
            }
            baseY = Core::kScreenTopHeight + Core::kScreenBottomHeight;
            baseX *= scaling;
            baseY *= scaling;
            break;
    }

    unsigned scaledX = (unsigned int) (baseX * Settings::values.resolution_factor);
    unsigned scaledY = (unsigned int) (baseY * Settings::values.resolution_factor);

    // Update Libretro with our status
    struct retro_system_av_info info;
    info.timing.fps = 60.0;
    info.timing.sample_rate = 41000;
    info.geometry.aspect_ratio = (float) scaledX / (float) scaledY;
    info.geometry.base_height = scaledX;
    info.geometry.base_width = scaledY;
    info.geometry.max_width = scaledX;
    info.geometry.max_height = scaledY;
    if (!LibRetro::SetGeometry(&info)) {
        LOG_CRITICAL(Frontend, "Failed to update 3DS layout in frontend!");
    }

    LOG_INFO(Frontend, "Updating sizing: %u x %u", scaledX, scaledY);
    UpdateCurrentFramebufferLayout(scaledX, scaledY);
    NotifyClientAreaSizeChanged(std::pair<unsigned, unsigned>(scaledX, scaledY));
    OnMinimalClientAreaChangeRequest(std::pair<unsigned, unsigned>(scaledX, scaledY));

    if (hasOGL) {
        ResetGLState();
    }
}

bool EmuWindow_LibRetro::ShouldDeferRendererInit() const {
    // load_game doesn't always provide a GL context.
    return true;
}

bool EmuWindow_LibRetro::HasSubmittedFrame() {
    bool state = submittedFrame;
    submittedFrame = false;

    return state;
}
