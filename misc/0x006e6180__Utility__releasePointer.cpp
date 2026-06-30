// FUNC_NAME: Utility::releasePointer
// Address: 0x006e6180 - Releases a pointer-to-pointer and sets it to null, calling another cleanup function.
void __fastcall releasePointer(int* ptrToPtr)
{
    if (*ptrToPtr != 0)
    {
        // Internal cleanup function (likely destructor or release of the pointed-to object)
        FUN_004daf90(ptrToPtr);
        *ptrToPtr = 0;
    }
    return;
}