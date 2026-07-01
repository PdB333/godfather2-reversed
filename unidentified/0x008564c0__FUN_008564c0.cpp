// FUNC_NAME: SomeClass::destroy
// Function address: 0x008564c0
// Role: Destructor that destroys a subobject at offset 8 and calls a cleanup function pointer at offset 4.

struct SomeClass {
    // +0x00: unknown (likely vtable pointer)
    // +0x04: void (*cleanupFunc)(); // function pointer for custom cleanup
    // +0x08: SubObject subObject; // subobject to be destroyed
};

void __thiscall SomeClass::destroy(SomeClass* this)
{
    // Destroy the subobject at offset 8
    destroySubobject(reinterpret_cast<uint8_t*>(this) + 8);
    // Call the cleanup function pointer stored at offset 4
    this->cleanupFunc();
}