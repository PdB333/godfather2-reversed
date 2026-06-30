// FUNC_NAME: InputDevice::detectConnection
// Address: 0x004c39b0
// Role: Detects connection state of an input device (controller/joypad).
// Uses a state machine: expects state at +0x1c == 1 to proceed.
// Returns status codes:
// 0 - not ready (state != 1)
// 1 - callback returned error (non-0, non-1)
// 2 - device not found (both detection methods failed)
// 3 - fallback/default connection type
// 4 - type 1 (callback returned 1) or status == 1
// 5 - status == 2
// 6 - status == 3

int __fastcall InputDevice::detectConnection(int this) {
    // +0x1c: current state (must be 1 to proceed)
    if (*(int*)(this + 0x1c) != 1) {
        return 0;
    }

    uint local_c[2];
    local_c[0] = local_c[0] & 0xffffff00; // clear low byte (probably alignment)

    char result;
    // Try primary detection method (e.g., is device present?)
    if (sub_411240(local_c)) { // FUN_00411240 - likely device present check
        int connectionType = 1;
        // Check if custom callback is installed (+0x2c)
        if (*(void**)(this + 0x2c) != nullptr) {
            int callbackResult = ((int (*)(uint))((void**)(this + 0x2c)))(local_c[0]);
            if (callbackResult == 1) {
                // Callback indicates connection type 1, return 4
                *(int*)(this + 0x1c) = 2;
                return 4;
            }
            if (callbackResult != 0) {
                // Callback returned error, return 1
                *(int*)(this + 0x1c) = 2;
                return 1;
            }
            // callback returned 0, continue with connectionType = 1
        }
        // Store connection type as 1
        *(int*)(this + 0x20) = 1;
        // Store low byte of local_c[0] as device ID
        *(byte*)(this + 0x24) = (byte)local_c[0];
        // Use primary info function (+0x30 is device handle/index)
        uint status = sub_4D2A60(*(uint*)(this + 0x30));
        if (status <= 3) {
            // Fall through to switch
        } else {
            return 2; // invalid status
        }
        // Switch on status (0-3)
        switch (status) {
        default:
            sub_4C3C00(); // cleanup/fallback
            *(int*)(this + 0x1c) = 2;
            return 3;
        case 1:
            *(int*)(this + 0x1c) = 2;
            return 4;
        case 2:
            *(int*)(this + 0x1c) = 2;
            return 5;
        case 3:
            *(int*)(this + 0x1c) = 2;
            return 6;
        }
    } else {
        // Primary detection failed; try secondary method (e.g., device ready?)
        if (sub_4112B0(local_c)) { // FUN_004112b0 - ready check
            // Secondary detection succeeded
            int connectionType = 2;
            *(int*)(this + 0x20) = 2;
            *(byte*)(this + 0x24) = (byte)local_c[0];
            uint status = sub_4D2AC0(*(uint*)(this + 0x30));
            if (status > 3) {
                return 2;
            }
            // Switch on status (same as above)
            switch (status) {
            default:
                sub_4C3C00();
                *(int*)(this + 0x1c) = 2;
                return 3;
            case 1:
                *(int*)(this + 0x1c) = 2;
                return 4;
            case 2:
                *(int*)(this + 0x1c) = 2;
                return 5;
            case 3:
                *(int*)(this + 0x1c) = 2;
                return 6;
            }
        } else {
            // Both detection methods failed
            return 2;
        }
    }
}