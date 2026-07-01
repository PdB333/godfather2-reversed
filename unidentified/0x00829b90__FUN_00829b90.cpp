// FUNC_NAME: SomeManager::someMethod
void SomeManager::someMethod(void* param_1) {
    // Get global manager instance (e.g., InputManager, ControllerManager)
    void** globalManager = (void**)FUN_009c8f80(); // likely returns a pointer to a singleton

    // Stack struct with fields: unknown1=2, unknown2=0x10, unknown3=0
    struct SomeStruct {
        int field0; // +0x00
        int field4; // +0x04
        int field8; // +0x08
    };
    SomeStruct localStruct;
    localStruct.field0 = 2;
    localStruct.field4 = 0x10;
    localStruct.field8 = 0;

    // Call a method on the global manager via its vtable (first entry)
    (*(void (**)(void*, SomeStruct*))*globalManager)(param_1, &localStruct);
}