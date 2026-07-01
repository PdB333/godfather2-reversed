// FUNC_NAME: GameConfig::getPlatformSpecificData
int GameConfig::getPlatformSpecificData(void *thisPtr) {
    int flagExists;
    int platformHash;

    flagExists = internalCheckFlag(thisPtr, 0);  // +0x? check bit/increment
    if (flagExists != 0) {
        platformHash = getPlatformIdentifierHash();  // FUN_0043aaf0
        if ((platformHash == 0x369ac561) || (platformHash == 0xa0d329d6)) {
            return g_platformSpecificValue1;  // DAT_0112fdd4
        }
        if ((platformHash == 0x10e5319e) || (platformHash == 0xa5976eb2)) {
            return g_platformSpecificValue2;  // DAT_0112fdd8
        }
    }
    return 0;
}