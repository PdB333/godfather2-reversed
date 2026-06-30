// FUNC_NAME: forwardFunction0x55f8b0
void __fastcall forwardFunction0x55f8b0(void* ignoredThis, int argument) {
    // This is a simple forwarder: ignores the this pointer (ecx) and calls
    // another function with the argument passed in edx.
    // Typically used as a wrapper or thunk for redirecting calls.
    // The called function is at 0x5605b0 (unknown purpose).
    FUN_005605b0(argument);
}