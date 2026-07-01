// FUNC_NAME: setterAtOffset0x14
void __thiscall setFieldAt0x14(void* thisPointer, uint value)
{
    // Offset +0x14: likely a pointer or integer field (e.g., owner handle, ID, or state)
    *(uint*)((char*)thisPointer + 0x14) = value;
}