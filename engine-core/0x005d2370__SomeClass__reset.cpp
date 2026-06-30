// FUNC_NAME: SomeClass::reset
// Address: 0x005d2370
// Role: Cleanup/reset method for a game object, releasing two allocated sub-objects and zeroing fields.

void __fastcall SomeClass::reset(int thisPtr)
{
    // Call first cleanup sub-function
    FUN_005d2620(thisPtr);

    // Zero out fields at offsets +0xC8 (200) and +0xC4
    *(int*)(thisPtr + 0xC8) = 0;
    *(int*)(thisPtr + 0xC4) = 0;

    // Release object at +0xC0 if non-null (via global allocator vtable)
    if (*(int*)(thisPtr + 0xC0) != 0) {
        // DAT_012234ec is a global pointer; +4 gives allocator vtable; offset 4 is release function
        (**(code**)(**(int**)(DAT_012234ec + 4) + 4))(*(int*)(thisPtr + 0xC0), 0);
    }
    *(int*)(thisPtr + 0xC0) = 0;

    // Call second cleanup sub-function
    FUN_005d1910();

    // Zero out fields at offsets +0x18 and +0x14
    *(int*)(thisPtr + 0x18) = 0;
    *(int*)(thisPtr + 0x14) = 0;

    // Release object at +0x10 if non-null (same allocator pattern)
    if (*(int*)(thisPtr + 0x10) != 0) {
        (**(code**)(**(int**)(DAT_012234ec + 4) + 4))(*(int*)(thisPtr + 0x10), 0);
    }
    *(int*)(thisPtr + 0x10) = 0;
}