// Copyright 2018 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#ifdef _WIN32
#include <windows.h>

#include <wincon.h>
#endif

#include "citra_qt/debugger/console.h"
#include "citra_qt/ui_settings.h"
#include "common/logging/backend.h"

namespace Debugger {
void ToggleConsole() {
#ifdef _WIN32
    if (UISettings::values.show_console) {
        if (AllocConsole()) {
            freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
            freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
            freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
            Log::AddBackend(std::make_unique<Log::ColorConsoleBackend>());
        }
    } else {
        if (FreeConsole()) {
            // In order to close the console, we have to also detach the streams on it.
            // Just redirect them to NUL if there is no console window
            Log::RemoveBackend(Log::ColorConsoleBackend::Name());
            freopen_s((FILE**)stdin, "NUL", "r", stdin);
            freopen_s((FILE**)stdout, "NUL", "w", stdout);
            freopen_s((FILE**)stderr, "NUL", "w", stderr);
        }
    }
#endif
}
} // namespace Debugger
