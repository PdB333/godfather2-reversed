// FUNC_NAME: getFieldAt0x80
unsigned int __fastcall getFieldAt0x80(int thisPtr)
{
    // Returns the value stored at offset +0x80 from this object.
    // This is a simple field getter; the exact semantics depend on the class.
    return *(unsigned int *)(thisPtr + 0x80);
}