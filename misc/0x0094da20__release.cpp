// FUNC_NAME: release
// Address: 0x0094da20
// Role: Decrements reference count at object offset 0x94. If count reaches zero, calls cleanup function (FUN_005c1b40).
void __thiscall release(int thisPtr)
{
    int *pRefCount = (int *)(thisPtr + 0x94); // ref count field
    (*pRefCount)--;
    if (*pRefCount == 0)
    {
        FUN_005c1b40(); // destruction or disposal
    }
}