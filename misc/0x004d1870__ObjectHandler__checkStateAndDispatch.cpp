// FUNC_NAME: ObjectHandler::checkStateAndDispatch
void __thiscall ObjectHandler::checkStateAndDispatch(ObjectHandler* thisObj) {
    // +0xa8: flags byte (bit 1 used for check)
    // +0xb0: status/error code
    // +0xb8: some value (e.g. timestamp or state index)
    // +0xbc: validation result
    int* pInt0xB0 = reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(thisObj) + 0xB0);
    uint8_t* pFlags0xA8 = reinterpret_cast<uint8_t*>(thisObj) + 0xA8;
    int* pValue0xB8 = reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(thisObj) + 0xB8);
    int* pResult0xBC = reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(thisObj) + 0xBC);

    // Check global system state (e.g., game mode, network ready)
    int globalState = checkGlobalState(&g_GlobalData); // FUN_00ac2870
    if (globalState != 1) {
        *pInt0xB0 = -102; // 0xffffff9a = -102, possibly error code
        return;
    }

    // Fetch current value (e.g., timestamp, tick count, or sequence)
    int currentValue = readCurrentValue(); // FUN_00ac28b0
    *pValue0xB8 = currentValue;

    // If flag bit 1 is not set, attempt validation
    if ((*pFlags0xA8 & 2) == 0) {
        int validationResult = validateValue(currentValue); // FUN_00abe220
        *pResult0xBC = validationResult;
        if (validationResult != 0) {
            handleSuccessPath(); // FUN_004d1ab0
            return;
        }
    }

    // Default fallback path
    handleDefaultPath(); // FUN_004d1a30
}