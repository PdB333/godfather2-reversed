// FUNC_NAME: GameManager::cleanupOrDestructor
void __thiscall GameManager::cleanup(undefined4* this) {
    // Set vtable to base class vtable
    *this = &BASE_CLASS_VTABLE;
    this[0xf] = (undefined4*)0x00d81ca4; // vtable entry or function pointer
    this[0x12] = (undefined4*)0x00d81ca0; // another vtable entry

    // Destroy dynamically allocated object at offset +0x50 (0x14 * 4)
    if (this[0x14] != 0) {
        destroyObject((void*)(this + 0x14));
        freeMemory((void*)(this + 0x14));
    }

    // Clean up global static objects
    destroyObject(&g_GlobalObject1);
    destroyObject(&g_GlobalObject2);
    destroyObject(&g_GlobalObject3);

    // Free raw pointers at offsets +0x58 and +0x60
    if (this[0x16] != 0) {
        freeMemory((void*)(this + 0x16));
    }
    if (this[0x18] != 0) {
        freeMemory((void*)(this + 0x18));
    }

    // Perform global shutdown
    globalShutdown();
}