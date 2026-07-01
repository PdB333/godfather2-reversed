// FUNC_NAME: safeGetGlobalValue
int safeGetGlobalValue(int enableFlag) {
    // If the flag is nonzero, retrieve the value from the global object pointer.
    // DAT_01131014 is a global pointer to a manager or singleton.
    // FUN_0043b870 likely returns some property from that object.
    if (enableFlag != 0) {
        return FUN_0043b870(gGlobalObject); // gGlobalObject assumed at 0x01131014
    }
    return 0;
}