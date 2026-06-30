// FUNC_NAME: SomeUnknownClass::lazyInitAndProcess
void SomeUnknownClass::lazyInitAndProcess(int param1, int param2) {
    // Check if the flag at offset 4 (byte) is zero
    if (*(char*)(this + 4) == 0) {
        // Call init function with zero and the first member (pointer at offset 0)
        FUN_00535450(0, *(int*)this);  // Could be initResource(0, this->resourcePtr)
        // Set flag to 1
        *(char*)(this + 4) = 1;
    }
    // Call process function with given parameters, plus constants 0,1,0
    FUN_0060cd00(param1, param2, 0, 1, 0);  // Could be processSomething(param1, param2, 0, 1, 0)
}