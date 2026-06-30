// FUNC_NAME: SomeManager::~SomeManager
void __thiscall SomeManager::~SomeManager()
{
    // Set vtable pointers for multiple inheritance
    // Offset 0x00: base class vtable pointer
    this->baseVtable = &PTR_LAB_00d63090;
    // Offset 0x70 (0x1c * 4): second base class vtable pointer
    this->secondBaseVtable = &PTR_LAB_00d64708;

    // If field at +0x68 (0x1a * 4) is non-null, free it
    // FUN_004daf90 likely performs deallocation (e.g., operator delete)
    if (this->allocatedBuffer != nullptr) { // +0x68
        free(this->allocatedBuffer); // FUN_004daf90 - assumed memory free
    }

    // Global cleanup function (e.g., module shutdown)
    // FUN_0080ea60 - likely a singleton or static deinitializer
    globalCleanup();
}