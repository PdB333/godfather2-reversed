// FUNC_NAME: InputManager::setControllerDeadzoneSensitivity
void __thiscall InputManager::setControllerDeadzoneSensitivity(int thisPtr, int deadzone, int sensitivity)
{
    // Store new deadzone and sensitivity values
    *(int *)(thisPtr + 0xF4) = deadzone;    // +0xF4: controllerDeadzone
    *(int *)(thisPtr + 0xF8) = sensitivity; // +0xF8: controllerSensitivity

    // If this is the global input manager instance, update the active device settings
    if (DAT_012058e8 == thisPtr) {
        FUN_0060ac80(
            *(int *)(thisPtr + 0x14),    // +0x14: pointer to device or owner (e.g., XInputState)
            *(int *)(thisPtr + 0xF0),    // +0xF0: previous deadzone value (for comparison)
            (int *)(thisPtr + 0xF4)      // pointer to new deadzone (triggers update)
        );
    }
}