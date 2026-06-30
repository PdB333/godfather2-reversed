// FUNC_NAME: SomeClass::getArrayEntry

// 0043c2a0 - Accessor that retrieves a dword from an array of 0x1c-byte structures.
// The class has a pointer at offset +0x04 to a memory region; the array begins at offset 0x10
// from that pointer. Each element is 0x1c bytes wide, and the first dword is returned.

uint __thiscall SomeClass::getArrayEntry(int index)
{
    // +0x04: pointer to a structure containing an array at offset 0x10
    // Element stride: 0x1c (28 bytes)
    return *(uint *)(*(int *)(this + 4) + 0x10 + index * 0x1c);
}