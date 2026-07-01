// FUNC_NAME: SomeClass::cleanupResourceArray
void __thiscall SomeClass::cleanupResourceArray(void)
{
    // Free each pointer in the array of 12 resource pointers at offsets 0xE4 to 0x13C
    // Offsets are spaced by 8 bytes each

    if (*(int*)(this + 0x13C) != 0) {
        freePointer((void**)(this + 0x13C));
    }
    if (*(int*)(this + 0x134) != 0) {
        freePointer((void**)(this + 0x134));
    }
    if (*(int*)(this + 0x12C) != 0) {   // 300 decimal = 0x12C
        freePointer((void**)(this + 0x12C));
    }
    if (*(int*)(this + 0x124) != 0) {
        freePointer((void**)(this + 0x124));
    }
    if (*(int*)(this + 0x11C) != 0) {
        freePointer((void**)(this + 0x11C));
    }
    if (*(int*)(this + 0x114) != 0) {
        freePointer((void**)(this + 0x114));
    }
    if (*(int*)(this + 0x10C) != 0) {
        freePointer((void**)(this + 0x10C));
    }
    if (*(int*)(this + 0x104) != 0) {
        freePointer((void**)(this + 0x104));
    }
    if (*(int*)(this + 0xFC) != 0) {
        freePointer((void**)(this + 0xFC));
    }
    if (*(int*)(this + 0xF4) != 0) {
        freePointer((void**)(this + 0xF4));
    }
    if (*(int*)(this + 0xEC) != 0) {
        freePointer((void**)(this + 0xEC));
    }
    if (*(int*)(this + 0xE4) != 0) {
        freePointer((void**)(this + 0xE4));
    }
}

// Helper: frees the pointer and sets it to NULL
void __fastcall freePointer(void** ptr)
{
    if (*ptr) {
        // operator delete or custom deallocation
        delete *ptr;
        *ptr = 0;
    }
}