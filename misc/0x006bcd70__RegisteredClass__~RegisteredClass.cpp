// FUNC_NAME: RegisteredClass::~RegisteredClass
void __thiscall RegisteredClass::~RegisteredClass(RegisteredClass* this)
{
    uint index;
    uint foundIndex;

    // Set vtable pointers (multiple inheritance)
    this->vtable = &VTABLE_00d5ea20;
    this[0xf].vtable = &VTABLE_00d5ea10;  // +0x3C
    this[0x12].vtable = &VTABLE_00d5ea0c; // +0x48

    // Remove this instance from global array
    index = 0;
    foundIndex = 0xffffffff;
    if (g_instanceCount != 0) {
        do {
            foundIndex = index;
            if (g_instanceArray[index] == this) break;
            index = index + 1;
            foundIndex = 0xffffffff;
        } while (index < g_instanceCount);
    }

    if (foundIndex != g_instanceCount - 1) {
        // Swap with the last element
        g_instanceArray[foundIndex] = g_instanceArray[g_instanceCount - 1];
    }

    g_instanceCount = g_instanceCount - 1;
    if (g_instanceCount == 0) {
        g_instanceCount = 0;
        operatorDelete(g_instanceArray);
        g_instanceArray = 0;
        g_instanceArrayCapacity = 0;
    }

    // Release global resources
    releaseGlobalResource(&DAT_01206778);
    releaseGlobalResource(&DAT_0120e93c);

    // Class-specific cleanup
    cleanupSpecific();

    // Free internal buffers
    if (this[0x1a] != 0) {         // +0x68
        operatorDelete(this[0x1a]);
    }
    if (this[0x17] != 0) {         // +0x5C
        operatorDelete(this[0x17]);
    }

    // Finalize global system
    finalizeGlobalSystem();
}