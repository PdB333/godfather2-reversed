// FUNC_NAME: ControllerManager::checkAndApplyRumble
// Address: 0x0091e330
// This function checks if a given controller index matches the active controller,
// and if rumble is enabled, applies rumble to that controller.

// Global pointer to the ControllerManager singleton
extern ControllerManager* g_controllerManager;

void ControllerManager::checkAndApplyRumble(int controllerIndex)
{
    // Get the active controller index via a virtual function call.
    // The vtable pointer is at offset +0x10 from the ControllerManager object.
    // The function at vtable+4 (second virtual function) returns the active controller index.
    int activeControllerIndex = (*(int (__thiscall*)(ControllerManager*))(*((int*)g_controllerManager + 0x10) + 4))(g_controllerManager);

    // Check if the given controller matches the active one and if rumble is enabled.
    // Offset +0x68 is a boolean flag indicating whether rumble is enabled.
    if (controllerIndex == activeControllerIndex && *(char*)((char*)g_controllerManager + 0x68) != '\0')
    {
        // Apply rumble with strength from offset +0x64 (100 decimal).
        // The first argument (1) likely indicates the rumble motor or pattern.
        FUN_0091cd80(1, *(int*)((char*)g_controllerManager + 100));
    }
}