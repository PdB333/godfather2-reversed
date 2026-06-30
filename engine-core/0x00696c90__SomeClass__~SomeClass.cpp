// FUNC_NAME: SomeClass::~SomeClass
// Address: 0x00696c90
// Role: Destructor that frees a managed pointer at +0x4, zeros both +0x4 and +0x8, and logs debug info before deletion.
void __thiscall SomeClass::~SomeClass(void) {
    char debugBuffer[8]; // +0x0 (local 8-byte buffer for debug formatting)

    // Format debug string using the object pointer and the managed resource pointer (twice passed)
    // The callee at 0x00695e30 likely writes a formatted message into debugBuffer
    FormatDebugString(debugBuffer, this, *(void**)(this + 0x4), this, *(void**)(this + 0x4));

    // Free the dynamically allocated resource pointed to by field at +0x4
    FreeMemory(*(void**)(this + 0x4)); // Calls 0x009c8eb0 (likely operator delete or MemoryManager::Free)

    // Clear both pointers to avoid dangling references
    *(void**)(this + 0x4) = nullptr;
    *(void**)(this + 0x8) = nullptr;

    return;
}