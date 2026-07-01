// FUNC_NAME: InputDeviceManager::isAnyControllerConnected
bool __thiscall InputDeviceManager::isAnyControllerConnected(void) {
    // Retrieve singleton input manager and call its update virtual at +0x30
    int *singleton = (int *)getInputDeviceManagerSingleton(); // FUN_00716430
    ((void(__thiscall *)(int))(*singleton + 0x30))(singleton); // call update

    uint count = *(uint *)(this + 0x68); // number of controller slots
    if (count != 0) {
        for (uint i = 0; i < count; i++) {
            // Array of 8‑byte entries at this+0x64, each contains a pointer/handle
            int slotEntry = *(int *)(*(int *)(this + 100) + i * 8);
            int adjusted = 0;
            if (slotEntry != 0) {
                adjusted = slotEntry - 0x48; // shift from a member offset back to base object
            }
            int result = getControllerFloatState(adjusted); // FUN_0071ce70 – returns non‑zero if valid
            if (result != 0) {
                char active = isControllerActive((float)extraout_ST0); // FUN_0071c320 – FPU float from previous op
                if (active != '\0') {
                    return true;
                }
            }
        }
    }
    return false;
}