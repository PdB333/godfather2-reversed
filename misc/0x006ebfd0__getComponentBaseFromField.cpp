// FUNC_NAME: getComponentBaseFromField
void* __fastcall getComponentBaseFromField(void* object)
{
    // Check if the pointer stored at offset 0x1ed8 in the object is non-null.
    // If it is, compute the base pointer of the containing structure by subtracting 0x48.
    // This is a common pattern to recover a parent object from a member pointer.
    int* memberPtr = *(int**)((char*)object + 0x1ed8);
    if (memberPtr)
    {
        return (void*)((char*)memberPtr - 0x48);
    }
    return nullptr;
}