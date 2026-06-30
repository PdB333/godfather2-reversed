// FUNC_NAME: UnknownClass::releaseSubObject
// Function address: 0x006a9230
// Role: Releases a sub-object pointed to by field at +0x14 if present, then clears the pointer.
// Returns 1 (success) always.

int __fastcall UnknownClass::releaseSubObject(int thisPtr)
{
    int* subObjectPtr = *(int**)(thisPtr + 0x14); // +0x14: pointer to sub-object (e.g., resource, child object)
    if (subObjectPtr != 0) {
        FUN_005e6660(subObjectPtr);               // Call destructor/free on sub-object (likely at 0x005e6660)
        *(int*)(thisPtr + 0x14) = 0;               // Clear pointer to avoid double-free
    }
    return 1;
}