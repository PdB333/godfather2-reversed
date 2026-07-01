// FUNC_NAME: SomeClass::~SomeClass (destructor at 0x007c0910)
void __fastcall SomeClass::Destroy(SomeClass* this)
{
    // this is __fastcall, so 'this' is in ecx
    // Access member at offset 0x58 (param_1[0x16]) -> pointer to companion object
    int* companionObj = this->field_0x58; // iVar1, offset 0x58

    // Set vtable to first vtable (some derived class)
    this->vtable = &PTR_LAB_00d6e354;

    // Call cleanup functions with magic IDs (likely resource manager IDs)
    MemoryManager::Release(0x20);
    MemoryManager::Release(0x57);

    // Some engine shutdown / component teardown
    EngineShutdown();

    // Unregister something with ID 0x1ff
    UnregisterID(0x1ff);

    // Release a handle stored at offset 0x94 (param_1[0x25])
    if (this->field_0x94 != 0) {
        ReleaseHandle(this->field_0x94);
    }

    // Another resource cleanup
    MemoryManager::Release(0x31);

    // Clear a flag in companion object at offset 0x249c
    companionObj[0x249c] &= ~0x8000; // Clear bit 15

    // If pointer at offset 0x98 (param_1[0x26]) is not null, delete it
    if (this->field_0x98 != 0) {
        DeleteObject(this->field_0x98); // presumably a destructor call
    }

    // Switch vtable to base class vtable (for base destructor chain)
    this->vtable = &PTR_LAB_00d6b95c;

    // Call base class destructor
    BaseClass::~BaseClass(this); // function at 0x0080ea60
}