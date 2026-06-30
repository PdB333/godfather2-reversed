// FUNC_NAME: gameUpdate
void gameUpdate(void)
{
    // +0x34: function pointer to global update hook (optional)
    code* pGlobalHook = *(code**)(DAT_012234c4 + 0x34);
    if (pGlobalHook != (code*)0x0) {
        (*pGlobalHook)();
    }

    // Update all registered subsystems
    // g_nSystemCount (DAT_011946b4) = number of active systems
    // g_pSystems (DAT_011946b8) = array of pointers to system objects
    // Each system has a tick/update method at offset +0x18
    for (int i = 0; i < DAT_011946b4; i++) {
        void* pSystem = (void*)((int*)DAT_011946b8)[i];      // each element is a pointer to a system object
        code* pSystemUpdate = *(code**)((int)pSystem + 0x18); // +0x18: update method pointer
        (*pSystemUpdate)();
    }

    // Post-update / late tick
    FUN_004e2480();
}