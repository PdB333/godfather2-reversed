// FUNC_NAME: SomeClass::destroyChildrenAndCleanup
void __thiscall SomeClass::destroyChildrenAndCleanup() {
    // Iterate linked list of child objects starting at this+0x00
    void* pCurrent = *reinterpret_cast<void**>(this); // +0x00: first child
    while (pCurrent) {
        // Each child node: +0x00 = vtable/object start, +0x04 = next pointer
        void* pNext = *reinterpret_cast<void**>(reinterpret_cast<char*>(pCurrent) + 4);
        // Call cleanup handler at vtable/table + 4 (release function) with child and 0
        typedef void (*ReleaseFunc)(void*, int);
        ReleaseFunc release = reinterpret_cast<ReleaseFunc>(
            (*reinterpret_cast<int**>(reinterpret_cast<int*>(this)[4]))[1] // offset 0x10 -> +0x04
        );
        release(pCurrent, 0);
        pCurrent = pNext;
    }
    // Handle special child at this+0x0C
    void* pSpecial = reinterpret_cast<void*>(reinterpret_cast<int*>(this)[3]); // +0x0C
    if (pSpecial) {
        typedef void (*ReleaseFunc)(void*, int);
        ReleaseFunc release = reinterpret_cast<ReleaseFunc>(
            (*reinterpret_cast<int**>(reinterpret_cast<int*>(this)[4]))[1] // same release func
        );
        release(pSpecial, 0);
    }
    // Call final cleanup from table at offset 0x0C (function pointer, no arguments)
    typedef void (*FinalCleanupFunc)();
    FinalCleanupFunc finalCleanup = reinterpret_cast<FinalCleanupFunc>(
        (*reinterpret_cast<int**>(reinterpret_cast<int*>(this)[4]))[3] // +0x0C
    );
    finalCleanup();
}