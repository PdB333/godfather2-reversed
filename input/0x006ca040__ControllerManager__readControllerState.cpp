// FUNC_NAME: ControllerManager::readControllerState
void __thiscall ControllerManager::readControllerState(
    int controllerIndex,            // this+0x6c
    float *outAxis0X,              // param_2
    float *outAxis0Y,              // param_3
    float *outAxis1X,              // param_4
    float *outAxis1Y,              // param_5
    float deadzone,                // param_6
    float sensitivity,             // param_7
    byte *outButtonA,              // param_8
    byte *outButtonB               // param_9
)
{
    // Global pointer to controller state array (e.g., g_pXInputState or g_pControllerManager)
    // DAT_012233a0: address of pointer to controller state base
    // +0x4: offset to first controller? Possibly a pointer to an array of controller states
    int *pControllerStateBase = *(int **)(DAT_012233a0 + 4);
    int *pController = nullptr;
    if (pControllerStateBase != nullptr)
    {
        pController = *pControllerStateBase; // dereference to get actual controller object
    }

    // Check if controller is valid or in special disconnected state (0x1f30)
    // Also check flag at offset 0x570, bit 0x14 (20) – likely "connected" or "active"
    bool controllerValid = (pController != nullptr) 
                        && (pController != (int*)0x1f30) 
                        && ((*(uint*)(pController + 0x570) >> 0x14) & 1) != 0;

    if (!controllerValid)
    {
        // Controller not valid, zero out all outputs
        *outAxis0X = 0.0f;
        *outAxis0Y = 0.0f;
        *outAxis1X = 0.0f;
        *outAxis1Y = 0.0f;
        *outButtonA = 0;
        *outButtonB = 0;
        return;
    }

    // Additional check: controllerIndex must be valid and global input enabled flag set
    if (controllerIndex != -1 && g_bInputEnabled != '\0') // DAT_00e50fb5 is likely a bool flag
    {
        // Read left stick (axis 0)
        readAxis(0, outAxis0X, outAxis0Y, deadzone, sensitivity);
        // Read right stick (axis 1)
        readAxis(1, outAxis1X, outAxis1Y, deadzone, sensitivity);

        // Get raw button state (e.g., XInput gamepad buttons packed)
        *outButtonA = getRawButtonState(); // FUN_006c9fe0

        // Map controllerIndex + button to specific action (e.g., map to game action)
        if (controllerIndex != -1 && g_bInputEnabled != '\0')
        {
            *outButtonB = mapControllerInputToAction(*(byte*)(this + 0x6c), 1, 2); // FUN_00410280
        }
        else
        {
            *outButtonB = 0;
        }
    }
    else
    {
        // Either invalid index or input disabled, zero outputs
        *outAxis0X = 0.0f;
        *outAxis0Y = 0.0f;
        *outAxis1X = 0.0f;
        *outAxis1Y = 0.0f;
        *outButtonA = 0;
        *outButtonB = 0;
    }
}