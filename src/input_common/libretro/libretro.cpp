// Copyright 2017 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <cmath>
#include <memory>
#include <unordered_map>
#include <libretro.h>
#include "common/logging/log.h"
#include "common/math_util.h"
#include "input_common/libretro/libretro.h"

namespace InputCommon {

namespace LibRetro {

// TODO: Should this be outside of LibRetro's namespace?
static retro_input_state_t input_state_cb;

class LibRetroButtonFactory;
class LibRetroAxisFactory;

class LibRetroButton final : public Input::ButtonDevice {
public:
    explicit LibRetroButton(int joystick_, int button_)
            : joystick(joystick_), button(button_) {}

    bool GetStatus() const override {
        return CheckButton((unsigned int) joystick, RETRO_DEVICE_JOYPAD, 0, (unsigned int) button) > 0;
    }

private:
    int joystick;
    int button;
};

/// A button device factory that creates button devices from LibRetro joystick
class LibRetroButtonFactory final : public Input::Factory<Input::ButtonDevice> {
public:
    /**
     * Creates a button device from a joystick button
     * @param params contains parameters for creating the device:
     *     - "joystick": the index of the joystick to bind
     *     - "button": the index of the button to bind
     */
    std::unique_ptr<Input::ButtonDevice> Create(const Common::ParamPackage& params) override {
        const int joystick_index = params.Get("joystick", 0);

        const int button = params.Get("button", 0);
        return std::make_unique<LibRetroButton>(joystick_index, button);
    }
};

/// A axis device factory that creates axis devices from LibRetro joystick
class LibRetroAxis final : public Input::AnalogDevice {
public:
    explicit LibRetroAxis(int joystick_, int button_)
            : joystick(joystick_), button(button_) {}

    std::tuple<float, float> GetStatus() const override {
        auto axis_x = (float) CheckButton((unsigned int) joystick, RETRO_DEVICE_ANALOG, (unsigned int) button, 0);
        auto axis_y = (float) CheckButton((unsigned int) joystick, RETRO_DEVICE_ANALOG, (unsigned int) button, 1);
        return std::make_tuple(axis_x / INT16_MAX, -axis_y / INT16_MAX);
    }

private:
    int joystick;
    int button;
};

/// A axis device factory that creates axis devices from SDL joystick
class LibRetroAxisFactory final : public Input::Factory<Input::AnalogDevice> {
public:
    /**
     * Creates a button device from a joystick button
     * @param params contains parameters for creating the device:
     *     - "joystick": the index of the joystick to bind
     *     - "button"(optional): the index of the button to bind
     *     - "hat"(optional): the index of the hat to bind as direction buttons
     *     - "axis"(optional): the index of the axis to bind
     *     - "direction"(only used for hat): the direction name of the hat to bind. Can be "up",
     *         "down", "left" or "right"
     *     - "threshould"(only used for axis): a float value in (-1.0, 1.0) which the button is
     *         triggered if the axis value crosses
     *     - "direction"(only used for axis): "+" means the button is triggered when the axis value
     *         is greater than the threshold; "-" means the button is triggered when the axis value
     *         is smaller than the threshold
     */
    std::unique_ptr<Input::AnalogDevice> Create(const Common::ParamPackage& params) override {
        const int joystick_index = params.Get("joystick", 0);

        const int button = params.Get("axis", 0);
        return std::make_unique<LibRetroAxis>(joystick_index, button);
    }
};

int16_t CheckButton(unsigned port, unsigned device,
                                           unsigned index, unsigned id) {
    return input_state_cb(port, device, index, id);
}

void Init() {
    using namespace Input;
    RegisterFactory<ButtonDevice>("libretro", std::make_shared<LibRetroButtonFactory>());
    RegisterFactory<AnalogDevice>("libretro", std::make_shared<LibRetroAxisFactory>());
}

void Shutdown() {
    using namespace Input;
    UnregisterFactory<ButtonDevice>("libretro");
    UnregisterFactory<AnalogDevice>("libretro");
}

} // namespace LibRetro
} // namespace InputCommon

void retro_set_input_state(retro_input_state_t cb) {
    InputCommon::LibRetro::input_state_cb = cb;
}
