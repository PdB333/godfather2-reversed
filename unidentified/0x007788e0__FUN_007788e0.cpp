// FUNC_NAME: SomeGameObject::~SomeGameObject
// Address: 0x007788e0
// Destructor for SomeGameObject (likely a base class in EARS engine).
// Restores vtable to base class, cleans up sub-objects, frees allocated memory.

void __fastcall SomeGameObject::~SomeGameObject(SomeGameObject* this)
{
    int* pSomeMember; // piVar1

    // Set vtable to derived class vtable (overridden)
    this->vtable = &PTR_LAB_00d68390;                      // +0x00: vtable pointer
    this->field_0x70 = &PTR_LAB_00d68380;                  // +0x70: some sub-object vtable
    this->field_0x7C = &PTR_FUN_00d6836c;                  // +0x7C: function pointer or sub-vtable

    // Call base class destructor or general cleanup
    baseCleanup();                                          // FUN_007f75b0 :: likely ~BaseGameObject()

    // pSomeMember = offset 0x88 (this->field_0x88)
    pSomeMember = reinterpret_cast<int*>(this + 0x22);     // +0x88

    // Check if field_0x88 is non-zero and not equal to 0x48
    if (this->field_0x88 != 0 && this->field_0x88 != 0x48) {
        if (pSomeMember != nullptr && *pSomeMember != 0x48) {
            releaseResource(DAT_0112ded0);                 // FUN_0043b870 :: likely managing a resource
        }
        freePointer(this + 0x1F);                          // FUN_009af0a0 :: free memory at +0x7C
    }

    // Check bit 0 of field at offset 0x90
    if ((this->field_0x90 & 1) != 0) {
        unregisterDebugObject(&DAT_0112e028);              // FUN_004086d0 :: unregister from some list
    }

    // Free member at +0x88 if non-null
    if (pSomeMember != nullptr) {
        deleteObject(pSomeMember);                         // FUN_004daf90 :: operator delete
    }

    // Final cleanup
    finalCleanup();                                         // FUN_004083d0

    // Restore vtable to base class vtable (for after destruction)
    this->vtable = &PTR_LAB_00d63090;                      // +0x00: base vtable

    // Free member at +0x68 (this->field_0x68)
    if (this->field_0x68 != 0) {
        deleteObject(reinterpret_cast<void*>(this + 0x1A)); // FUN_004daf90 :: operator delete
    }

    // Last shutdown call
    shutdown();                                             // FUN_0080ea60
}