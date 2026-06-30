// FUNC_NAME: AptSound::isSoundSystemReady
bool AptSound::isSoundSystemReady(void) {
    char isAttempting = someInternalCheck(); // FUN_005a8030 - returns nonzero if sound system is being attempted
    if (isAttempting) {
        // Log assertion/error: file "..\\source\\Apt\\AptSound.cpp", line 66, severity 2 (likely error), message constant
        logAssert("..\\source\\Apt\\AptSound.cpp", 0x42, 2, DAT_011291d0); // FUN_0059bf00
    }
    return DAT_0119cbbc; // global sound system active flag (bool)
}