// FUNC_NAME: DebugConsoleManager::checkToggleInput
// Address: 0x00931b80
// Purpose: Checks for debug console toggle key combination (Alt/Ctrl/Windows + backtick?).
// Returns: 1 if console toggled/opened, otherwise result from keyboard handler update.
int DebugConsoleManager::checkToggleInput(uint msgWParam, uint msgLParam) {
    char consoleToggleKeyPressed; // local_5: stores if the backtick/console key is down
    bool isModifierKeyPressed;

    // Global: active debug console flag (0x0113054c)
    auto* inputSettings = reinterpret_cast<uint8_t*>(DAT_012233b4); // +0x53d is a byte field

    consoleToggleKeyPressed = '\0';

    // Check if any of the modifier keys (Alt, Ctrl, Left/Right Win, Apps) are held
    if (GetAsyncKeyState(VK_MENU) != 0 ||
        GetAsyncKeyState(VK_CONTROL) != 0 ||
        GetAsyncKeyState(VK_LWIN) != 0 ||
        GetAsyncKeyState(VK_RWIN) != 0 ||
        GetAsyncKeyState(VK_APPS) != 0) {
        // Modifier is held: set the global flag to show console is "open by modifier"
        g_debugConsoleActive = '\x01';
    } else {
        // No modifier: check the actual console toggle key (likely backtick `, VK_OEM_3)
        if (g_debugConsoleActive == '\0') {
            isModifierKeyPressed = FUN_00411240(&consoleToggleKeyPressed); // key check function
            if (!isModifierKeyPressed) goto checkMouseButton;
        } else {
            isModifierKeyPressed = FUN_00411240(&consoleToggleKeyPressed);
            if (isModifierKeyPressed) {
                // if key pressed while console already active, clear flag
                g_debugConsoleActive = '\0';
                goto checkMouseButton;
            } // else: keep console active (modifier released but console key still down?)
        }

        if (consoleToggleKeyPressed != '\0') {
            // Console toggle key pressed: open/close console
            FUN_00411220(); // maybe start console display
            FUN_00931130(); // likely clear input buffer or reset
            FUN_00931010(); // show console or something
            return 1;
        }

        // Check for mouse button (e.g., right-click)
        if (FUN_00410de0() != 0) {
            goto handleConsoleOpen;
        }

        // Check another key from input settings (byte at globals+0x53d)
        uint keyCode = (uint)(*(int8_t*)((uint8_t*)inputSettings + 0x53d)); // sign-extended
        if (FUN_00410280(keyCode, 0xffff, 2) != 0) {
            // That key triggered (mouse button simulation?)
            goto handleConsoleOpen;
        }
    }

checkMouseButton:
    // If we came here, no console toggling happened
    // Fall through to update keyboard handler
    int updateResult = FUN_009310d0(msgWParam, msgLParam);
    if (updateResult == 1) {
        FUN_00411220(); // console opened by some event
    }
    return updateResult;

handleConsoleOpen:
    // This label is only reached if a modifier key was held,
    // or if the console key was pressed, or mouse/key combo triggered.
    // In those cases, we open/keep console open.
    // (Note: flow from modifier key path directly set g_debugConsoleActive and then jumps here)
    int updateResult2 = FUN_009310d0(msgWParam, msgLParam);
    if (updateResult2 == 1) {
        FUN_00411220();
    }
    return updateResult2;
}