// FUNC_NAME: getContainingObjectFromPointer
int __fastcall getContainingObjectFromPointer(void* thisPtr)
{
    // +0x2d0: pointer to a sub-object (likely a component or child)
    void* subObjPtr = *(void**)((char*)thisPtr + 0x2d0);
    if (subObjPtr != nullptr) {
        // The sub-object is at offset 0x48 within its containing object.
        // Subtract that offset to get the base of the container.
        return (int)((char*)subObjPtr - 0x48);
    }
    return 0;
}