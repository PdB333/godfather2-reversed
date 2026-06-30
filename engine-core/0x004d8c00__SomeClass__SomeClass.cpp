// FUNC_NAME: SomeClass::SomeClass
// Address: 0x004d8c00
// Role: Constructor for a base-level object; initializes field at +0x14 to null and calls a sub-initializer

int __thiscall SomeClass::SomeClass(int thisPtr, int baseParam)
{
    // Clear the pointer at offset +0x14 (likely a vtable or derived data)
    *(int*)(thisPtr + 0x14) = 0;

    // Call the base class initializer (or a separate initialization routine)
    FUN_004da550(baseParam);

    return thisPtr;
}