// FUNC_NAME: UnknownClass::cleanup
// Reconstructed from 0x007463d0: Destructor-like cleanup for unknown object with sub-object management.
// Observed offsets:
//   this+0x00: vtable pointer (set to PTR_LAB_00d63e80 at start)
//   this+0x19: byte (bool flag? if set, triggers sub-object check)
//   this+0x58: int* (pointer to a sub-object with vtable at offset 0)
//   this+0x5C: int (pointer to another sub-object, cleaned via FUN_004daf90)
// The sub-object at +0x58 has a virtual function at vtable+0x25c called conditionally.
// Global cleanup via FUN_004ac1e0 after local cleanup.
void __fastcall UnknownClass::cleanup(UnknownClass* this)
{
    // Set vtable to base class vtable (likely for proper virtual dispatch during destruction)
    *reinterpret_cast<void**>(this) = &PTR_LAB_00d63e80;

    // Check flag at offset 0x19
    if (reinterpret_cast<const char*>(this)[0x19] != '\0')
    {
        int* subObject = reinterpret_cast<int*>(this)[0x16]; // offset 0x58
        if (subObject != nullptr)
        {
            // Check bit 0x19 (25) of dword at subObject+0x1F58 (0x7D6 * 4)
            if (((static_cast<uint>(subObject[0x7D6]) >> 0x19) & 1) == 0)
            {
                // Call virtual function at index 0x97 (0x25c/4) on subObject
                (reinterpret_cast<void(__thiscall*)(void*)>(reinterpret_cast<void**>(*subObject)[0x97]))(subObject);
            }
        }
    }

    // Clean up the sub-object at offset 0x5C (this[0x17])
    if (reinterpret_cast<int*>(this)[0x17] != 0)
    {
        FUN_004daf90(reinterpret_cast<char*>(this) + 0x5C);
    }

    // Global cleanup function
    FUN_004ac1e0();
}