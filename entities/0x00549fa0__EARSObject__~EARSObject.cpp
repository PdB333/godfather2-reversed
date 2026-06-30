// FUNC_NAME: EARSObject::~EARSObject
void __fastcall EARSObject::~EARSObject(void) {
    // +0x00 vtable pointer (set to base class vtable)
    this->vtable = &baseVtable;  // PTR_FUN_00e39bc8

    // +0xC0 pointer to a shared ref-counted resource (struct with: +0 vtable, +4 short flag, +6 short refCount)
    EARSRefCountedResource* pResource = reinterpret_cast<EARSRefCountedResource*>(this->field_0xC0);

    if (pResource != nullptr) {
        // Check if flag at offset 4 is non-zero
        if (pResource->flag != 0) {
            // Decrement reference count at offset 6
            pResource->refCount--;
            if (pResource->refCount == 0) {
                // Call the first virtual function (destroy/release) with argument 1
                pResource->vtable->destroy(1);
            }
        }
        // Clear the pointer
        this->field_0xC0 = nullptr;
    }

    return;
}