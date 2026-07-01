// FUNC_NAME: UIManager::loadScreen
void __thiscall UIManager::loadScreen(uint32 this, uint32 resourceName) {
    char isMultiplayer;
    int allocationPtr;
    undefined1 *parsedString;
    uint32 parsedLength1;
    uint32 parsedLength2;
    code *cleanupCallback;

    if ((*(byte *)(*(uint32 *)g_pGameManager + 0x14) & 1) != 0) { // +0x14: m_bInitialized
        parsedString = nullptr;
        parsedLength1 = 0;
        parsedLength2 = 0;
        cleanupCallback = nullptr;
        parseStringToStruct(&parsedString, resourceName); // may set callback/len
        uint32 resultFlag = 1;
        if (*(char *)(*(uint32 *)g_pMultiplayerStatus + 0x48) != '\0') { // +0x48: m_bMultiplayer
            isMultiplayer = checkMultiplayerEnabled();
            resultFlag = 1;
            if (isMultiplayer == '\0') {
                resultFlag = 0;
            }
        }
        setSubObjectReadyState((UISubObject*)(this + 0x24), resultFlag, 0); // +0x24: sub-object
        allocationPtr = allocateMemory(0x1c); // size 28, likely a struct
        if (allocationPtr == 0) {
            resultFlag = 0;
        } else {
            resultFlag = initSubObject((UISubObject*)(this + 0x24), 0);
        }
        undefined1 *finalString = parsedString;
        if (parsedString == nullptr) {
            finalString = (undefined1 *)&defaultResourceString;
        }
        loadResource(0, *(uint32 *)(this + 0x98), finalString); // +0x98: some ID
        doPostLoadStep1();
        doPostLoadStep2();
        if ((*(byte *)(this + 0x10) & 1) != 0) { // +0x10: m_bNeedsCleanup
            cleanupResources();
        }
        *(uint32 *)(this + 0x1c) = resultFlag;   // +0x1c: m_loadResult
        *(uint32 *)(this + 0x20) = 0;              // +0x20: m_loadState
        *(uint32 *)(this + 0x10) |= 1;             // +0x10: set m_bNeedsCleanup
        *(uint32 *)(this + 0x18) = 0;              // +0x18: m_unknown
        if (parsedString != nullptr) {
            (*cleanupCallback)(parsedString);      // free parsed string if callback set
        }
    }
}