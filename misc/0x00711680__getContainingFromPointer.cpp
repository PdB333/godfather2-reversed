// FUNC_NAME: getContainingFromPointer
// Address: 0x00711680
// Returns the containing object from a stored pointer at offset 0x338, adjusting by -0x48.
// If the stored pointer is null, returns 0.
int __fastcall getContainingFromPointer(int thisPtr)
{
    int storedPtr = *(int *)(thisPtr + 0x338);
    if (storedPtr != 0)
        return storedPtr - 0x48;
    return 0;
}