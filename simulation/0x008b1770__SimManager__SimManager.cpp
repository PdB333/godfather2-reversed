// FUNC_NAME: SimManager::SimManager
// Function address: 0x008b1770
// Role: Constructor for SimManager (or similar manager class). Sets up vtable pointers and initializes subobjects.

void __fastcall SimManager::SimManager(void* this) {
    // Set primary vtable pointer
    this->vtable = &gSimManagerVTable; // +0x00: *param_1 = &PTR_FUN_00d7ab60

    // Set secondary vtable pointers for additional interfaces (multiple inheritance)
    *(void**)((char*)this + 0x3C) = &gSimManagerOtherVTable1; // +0x3C: param_1[0xf] = &PTR_LAB_00d7ab50
    *(void**)((char*)this + 0x48) = &gSimManagerOtherVTable2; // +0x48: param_1[0x12] = &PTR_LAB_00d7ab4c

    // Initialize first sub-object at offset 0x50 (20 dwords into the struct)
    initSubObject1((SomeBaseClass*)((char*)this + 0x50)); // FUN_004086d0(param_1+0x14)
    resetSubObject((SomeBaseClass*)((char*)this + 0x50)); // FUN_00408310(param_1+0x14)

    // Initialize second sub-object at offset 0x58 (22 dwords)
    resetSubObject((SomeBaseClass*)((char*)this + 0x58)); // FUN_00408310(param_1+0x16)

    // Register this manager instance globally
    registerManagerInstance(); // FUN_0046c640()
}