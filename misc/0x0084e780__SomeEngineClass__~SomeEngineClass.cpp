// FUNC_NAME: SomeEngineClass::~SomeEngineClass
// Address: 0x0084e780
// Destructor for an object that owns a sub-object (likely a pointer). 
// Restores vtable, releases child, sets purecall vtable, then optionally deletes memory.

void __thiscall SomeEngineClass::~SomeEngineClass(byte isDealloc) {
    // Restore original vtable before destroying sub-object (avoids dangling virtual calls)
    this->vtable = &VTABLE_ORIGINAL; // 0xd74eb4

    // If child object (offset +0x04) is non-null, release it
    if (this->childObject != 0) {
        releaseChild(this->childObject); // FUN_004daf90 – likely destructor/cleanup
    }

    // Mark vtable as purecall (fully destructed)
    this->vtable = &VTABLE_PURECALL; // 0xe3924c

    // If the low bit of isDealloc is set, free the memory (operator delete)
    if ((isDealloc & 1) != 0) {
        operatorDelete(this); // FUN_009c8eb0 – typically calls free(ptr)
    }

    // Note: decompiler shows returning 'this', but destructors normally return void.
}