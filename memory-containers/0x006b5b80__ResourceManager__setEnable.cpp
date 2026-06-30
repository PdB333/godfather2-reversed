// FUNC_NAME: ResourceManager::setEnable
void __thiscall ResourceManager::setEnable(int thisPtr, int enable) // enable is 0 or 1
{
    int *refCountPtr;
    int index;
    bool isBit18Clear;

    *(int *)(thisPtr + 0xd4) = enable; // +0xd4: active flag

    // Activation sequence when becoming enabled
    if ((*(int *)(thisPtr + 0x16c) == 0) && (enable == 0) && // +0x16c: parent/source flag
        ((*(uint *)(thisPtr + 0x34) >> 0x1c & 1) == 0))    // +0x34: flags bit28
    {
        isBit18Clear = (*(uint *)(thisPtr + 0x34) >> 0x12 & 1) == 0; // bit18

        if (!isBit18Clear)
        {
            // bit18 set: clear bit16 and set bit19
            *(uint *)(thisPtr + 0x34) = *(uint *)(thisPtr + 0x34) & 0xfffbffff; // clear bit16 (0x40000)
            *(uint *)(thisPtr + 0x34) = *(uint *)(thisPtr + 0x34) | 0x80000;    // set bit19 (0x80000)
        }

        if ((*(byte *)(thisPtr + 0x36) & 1) == 0) // bit16 (lowest byte of +0x36)
        {
            if (isBit18Clear)
                goto LAB_006b5be6; // skip call
        }
        else
        {
            // bit16 set: clear it and set bit17
            *(uint *)(thisPtr + 0x34) = *(uint *)(thisPtr + 0x34) & 0xfffeffff; // clear bit16 (0x10000)
            *(uint *)(thisPtr + 0x34) = *(uint *)(thisPtr + 0x34) | 0x20000;    // set bit17 (0x20000)
        }
        FUN_006b4e30(1, 0); // notification/init call
    }

LAB_006b5be6:
    // Reference counting logic for enabled state
    if (enable == 0) // deactivate
    {
        refCountPtr = (int *)(thisPtr + 0x78); // +0x78: reference count
        *refCountPtr = *refCountPtr - 1;
        if (*refCountPtr == 0)
        {
            // Destroy all managed elements
            index = *(int *)(thisPtr + 0xac); // +0xac: element count
            while (index = index - 1, index >= 0)
            {
                FUN_006b56a0(index); // destroy element by index
            }
        }
    }
    else // activate
    {
        *(int *)(thisPtr + 0x78) = *(int *)(thisPtr + 0x78) + 1; // +0x78: ref count
        if ((*(int *)(thisPtr + 0x78) == 1) &&
            (index = *(int *)(thisPtr + 0x68) - *(int *)(thisPtr + 0xac), index > 0)) // +0x68: max capacity, +0xac: current count
        {
            do
            {
                FUN_006b4b50(); // create a new element
                index = index - 1;
            } while (index != 0);
            return;
        }
    }
    return;
}