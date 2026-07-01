// FUNC_NAME: SomeClass::SomeClass
// Function address: 0x00815700
// Constructor for a class that sets up multiple vtable pointers and calls base constructor
void __thiscall SomeClass::SomeClass(void *thisPtr)
{
    // Set primary vtable pointer at offset 0x00
    *(undefined4 **)thisPtr = &PTR_FUN_00d73158;
    // Set secondary vtable pointer at offset 0x3C (0xF * 4)
    *(undefined4 **)((char *)thisPtr + 0x3C) = &PTR_LAB_00d73148;
    // Set tertiary vtable pointer at offset 0x48 (0x12 * 4)
    *(undefined4 **)((char *)thisPtr + 0x48) = &PTR_LAB_00d73144;
    // Call base class constructor (likely at offset 0x00)
    FUN_00815be0(thisPtr);
    // Check if member at offset 0x58 (0x16 * 4) is non-null
    if (*(void **)((char *)thisPtr + 0x58) != 0)
    {
        // Call function pointer at offset 0x64 (0x19 * 4) with the member as argument
        (*(void (__thiscall **)(void *))((char *)thisPtr + 0x64))(*(void **)((char *)thisPtr + 0x58));
    }
    FUN_0046c640();
    return;
}