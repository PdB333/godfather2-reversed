// FUNC_NAME: SomeClass::conditionalDebugOutput

void __thiscall SomeClass::conditionalDebugOutput(void) {
    // +0x20: pointer to a debug output object (may be console, log, etc.)
    void* debugObject = *(void**)(this + 0x20);
    
    if (debugObject != 0) {
        // Call the debug print function with the global console/log handle
        FUN_0044fd00(DAT_012233a4); // DAT_012233a4: likely a global output stream or console object
    }
}