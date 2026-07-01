// FUNC_NAME: debug_executeOnComponent
void debug_executeOnComponent(int param_1)
{
    int managerPtr;

    if (param_1 != 0) {
        // From the global game manager, retrieve the component at offset 0xe4
        managerPtr = getGameManager(globalGameManagerInstance);  // DAT_0112a9fc -> global singleton
        executeComponentAction(*(int*)(managerPtr + 0xe4));
        return;
    }
    // Default global component (stored at 0x000000e4)
    executeComponentAction(globalDefaultComponent);
    return;
}