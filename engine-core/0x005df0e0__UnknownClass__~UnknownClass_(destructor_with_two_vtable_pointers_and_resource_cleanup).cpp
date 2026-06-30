// FUNC_NAME: UnknownClass::~UnknownClass (destructor with two vtable pointers and resource cleanup)
void __thiscall UnknownClass::~UnknownClass(void)
{
    // local_c: temporary buffer, likely for debug logging or cleanup helper
    char tempBuffer[12];

    // Call helper function with:
    // - tempBuffer (output)
    // - this pointer
    // - first 4 bytes of the allocated block at offset 0x1c (read as int)
    // - this pointer again (redundant)
    // - pointer to the allocated block itself
    FUN_005e0410(tempBuffer, this,
                 *(*reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 0x1c)),
                 this,
                 *reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 0x1c));

    // Delete the pointer at offset 0x1c via virtual function (vtable at +4, index 1)
    // The vtable belongs to first base class; the function is likely `free` or `deallocate`
    // Second parameter 0x18 is the size of the allocated block
    (*(void(__thiscall**)(int, int))(*reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 4) + 4))(
        *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x1c), 0x18);

    // Nullify both pointers at offsets 0x1c and 0x20
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x1c) = 0;
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x20) = 0;

    // If pointer at offset 0x18 is not null, delete it via second base vtable (+0x14, index 1)
    // Size 0 suggests array deletion or single-object with unspecified size
    if (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x18) != 0)
    {
        (*(void(__thiscall**)(int, int))(*reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 0x14) + 4))(
            *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x18), 0);

        // Nullify pointer at offset 0x18
        *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x18) = 0;
    }

    // Call fourth virtual function (index 3) of the second base's vtable (at +0x14)
    // This is likely a release/shutdown method
    (*(void(__thiscall**)(void))(*reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 0x14) + 0xc))();

    // Call final cleanup function (possibly base class destructor or memory deallocation)
    FUN_005df430();

    return;
}