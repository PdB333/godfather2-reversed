// Function address: 0x007326c0
// Role: Returns the owner object by subtracting 0x48 from a stored component pointer at offset +0x2680.
// FUNC_NAME: getParentFromComponentPointer
int __fastcall getParentFromComponentPointer(int thisPtr)
{
    // +0x2680 stores a pointer to some field inside the owner object (offset +0x48 within the owner)
    int componentPtr = *(int *)(thisPtr + 0x2680);
    if (componentPtr != 0) {
        return componentPtr - 0x48; // adjust to get the base of the owner object
    }
    return 0;
}