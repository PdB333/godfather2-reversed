// FUNC_NAME: ControllerManager::updateButtonState
// Address: 0x00763ff0
// Role: Updates the button state for a controller based on input bindings.
//        Sets member at offset 0xdc (mButtonState) to 0 (idle), 1 (pressed), or 2 (held).
//        Returns 1 if the button state was successfully determined and set.

// Internal helper functions for input binding lookup.
// FUN_006019b0: Likely primary binding lookup (inputDevice, actionID) returns binding entry pointer or 0.
// FUN_00601a00: Likely fallback/reverse binding lookup (actionID, inputDevice) returns binding entry pointer or 0.

// Assumed class layout (partial):
//   +0x00 ... (vtable, etc.)
//   +0x78 m_pControllerDeviceManager (pointer to controller device manager)
//   +0xdc mButtonState (int, current button action state)
// Inside controller device manager:
//   +0x7c m_pActiveController (pointer to active controller device)

static __fastcall int __fastcall ControllerManager::updateButtonState(int thisPtr)
{
    ushort flags;
    int bindingEntry;
    int result = 0;

    // Check if there is an active controller device
    int* pControllerDeviceMgr = *(int**)(thisPtr + 0x78);
    if (pControllerDeviceMgr != 0 && *(int*)(pControllerDeviceMgr + 0x7c) != 0)
    {
        int actionId1 = 1;
        int inputDevice1 = 2;

        // Try primary binding lookup (inputDevice, actionId)
        bindingEntry = FUN_006019b0(&actionId1, &inputDevice1);
        if (bindingEntry == 0)
        {
            // Swap and try fallback lookup (actionId, inputDevice)
            actionId1 = 2;
            inputDevice1 = 1;
            bindingEntry = FUN_00601a00(&inputDevice1, &actionId1);
            if (bindingEntry == 0)
            {
                return 0; // No binding mapping found
            }
        }

        // Read flags from binding entry at offset 0x10
        flags = *(ushort*)(bindingEntry + 0x10);

        // Determine button action state based on flags
        // Flag bit 2 (0x04): pressed
        if ((flags & 0x04) != 0)
        {
            *(int*)(thisPtr + 0xdc) = 1; // Pressed
            return 1;
        }
        // Flag bit 1 (0x02): released/idle
        if ((flags & 0x02) != 0)
        {
            *(int*)(thisPtr + 0xdc) = 0; // Idle
            return 1;
        }
        // Flag bit 5 (0x20): held
        result = 0;
        if ((flags & 0x20) != 0)
        {
            *(int*)(thisPtr + 0xdc) = 2; // Held
            result = 1;
        }
    }
    return result;
}