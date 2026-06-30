// FUNC_NAME: getConditionalGlobalData
uint32_t getConditionalGlobalData(int32_t enableFlag) {
    if (enableFlag != 0) {
        return FUN_0043b870(gSomeGlobal);  // gSomeGlobal at 0x01131018, likely a singleton or manager pointer
    }
    return 0;
}