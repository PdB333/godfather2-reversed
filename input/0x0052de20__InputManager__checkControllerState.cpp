// FUNC_NAME: InputManager::checkControllerState
uint __fastcall checkControllerState(int controllerIndex, int param1, int param2, int param3, int param4, int param5, int param6)
{
    uint flags = 0;
    if (controllerIndex > 0) {
        // If force index flag is zero, default to controller 1
        if (g_controllerForceIndex == 0) {
            controllerIndex = 1;
        }
        flags = controllerIndex << 8; // Bits 8-15 store controller index
    }
    if (param1 != 0) {
        flags |= 4;   // Bit 2
    }
    if (param2 != 0) {
        flags |= 0xc; // Bits 2 and 3
    }
    if (param3 != 0) {
        flags |= 0x10; // Bit 4
    }
    if (param4 != 0) {
        flags |= 1;    // Bit 0
    }
    if (param5 != 0) {
        flags |= 0x20; // Bit 5
    }
    if (param6 != 0) {
        flags |= 2;    // Bit 1
    }
    if (flags != g_expectedControllerFlags) {
        return updateControllerState();
    }
    return g_storedControllerResult;
}