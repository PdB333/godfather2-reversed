// FUNC_NAME: UnknownClass::getContainerFromPointer
int __fastcall UnknownClass::getContainerFromPointer(int thisPtr)
{
    // Check if pointer at offset +0x24FC is non-null
    int* internalPtr = *(int**)(thisPtr + 0x24FC);
    if (internalPtr != 0) {
        // Return a pointer 0x48 bytes before internalPtr (offset to containing struct)
        return (int)(internalPtr - 0x48);
    }
    return 0;
}