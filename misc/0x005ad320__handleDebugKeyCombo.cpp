// FUNC_NAME: handleDebugKeyCombo
void __cdecl handleDebugKeyCombo(int param_1, int param_2)
{
    char isDebugActive;
    uint* statePtr;
    uint stateValue;
    int actionId;
    int extraParam;

    isDebugActive = isDebugModeEnabled(0);
    if (isDebugActive != '\0') {
        statePtr = (uint*)getGlobalState();
        stateValue = *statePtr & 0x7fff;
        if (((*statePtr & 0x8000) != 0) && ((stateValue == 0xd || (stateValue == 0x12)))) {
            // Key combo detected: bit 15 set and lower 15 bits are 13 (Enter) or 18 (Left Alt?)
            getGlobalState(); // discard return? Possibly side effect
            actionId = getActionId(); // e.g., from current context
            extraParam = getGlobalState(param_2); // second call with param
            executeAction(actionId, extraParam, param_2);
        }
    }
}