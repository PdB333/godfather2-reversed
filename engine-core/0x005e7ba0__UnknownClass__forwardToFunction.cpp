// FUNC_NAME: UnknownClass::forwardToFunction
// Address: 0x005e7ba0
// Role: Thin wrapper that delegates to the actual implementation at 0x005e73f0.
// This appears to be a virtual override or an alias that forwards the call unchanged.

void UnknownClass::forwardToFunction(void* thisPtr, int param) {
    // Delegates directly to the implementation function
    // The target function likely performs the core logic for this operation
    FUN_005e73f0(thisPtr, param);
}