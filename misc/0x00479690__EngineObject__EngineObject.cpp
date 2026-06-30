// FUNC_NAME: EngineObject::EngineObject

void __fastcall EngineObject::EngineObject(EngineObject *this)
{
    // Set vtable pointer (class-specific function table)
    *(int **)this = &PTR_FUN_00e32fe4;          // vtable for this base class

    // Initialize member sub-objects
    // Sub-object at offset 0x50 (in bytes)
    SubObject *subObj1 = (SubObject *)((char *)this + 0x50);
    initSubObjectPart1(subObj1);    // FUN_004086d0
    initSubObjectPart2(subObj1);    // FUN_00408310

    // Sub-object at offset 0x58
    SubObject *subObj2 = (SubObject *)((char *)this + 0x58);
    initSubObjectPart1(subObj2);
    initSubObjectPart2(subObj2);

    // Sub-object at offset 0x60
    SubObject *subObj3 = (SubObject *)((char *)this + 0x60);
    initSubObjectPart1(subObj3);
    initSubObjectPart2(subObj3);

    // Sub-object at offset 0x68
    SubObject *subObj4 = (SubObject *)((char *)this + 0x68);
    initSubObjectPart1(subObj4);
    initSubObjectPart2(subObj4);

    // Sub-object at offset 0x7C (special: only part 2)
    SubObject *subObj5 = (SubObject *)((char *)this + 0x7C);
    initSubObjectPart2(subObj5);    // only part 2 called

    // Sub-object at offset 0x84
    SubObject *subObj6 = (SubObject *)((char *)this + 0x84);
    initSubObjectPart1(subObj6);
    initSubObjectPart2(subObj6);

    // Final global initialization
    initializeGlobalState();        // FUN_0046c640
}

// Helper functions (actual decompiled addresses)
// FUN_004086d0: Part 1 of sub-object initialization (e.g., clear flags, set defaults)
// FUN_00408310: Part 2 of sub-object initialization (e.g., link to parent)
// FUN_0046c640: Global state initialization (e.g., singleton registry)