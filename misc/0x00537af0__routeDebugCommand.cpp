// FUNC_NAME: routeDebugCommand
void __fastcall routeDebugCommand(void* param_1)
{
    int* pTarget;

    if (g_pActiveDebugManager == 0) {
        // Use the default debug manager's target at offset +0x20
        pTarget = *(int**)(g_pDefaultDebugManager + 0x20);
    } else {
        // Use the active debug manager's target at offset +0x18
        pTarget = *(int**)(g_pActiveDebugManager + 0x18);
    }

    if (pTarget != 0) {
        executeDebugCommand(g_pGlobalContext, pTarget, param_1);
    }
}