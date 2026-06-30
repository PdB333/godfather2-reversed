// FUNC_NAME: ManagedObject::releaseHandles
void ManagedObject::releaseHandles(void)
{
    // First handle at this+0x08
    int* pHandle1 = *(int**)(this + 8);
    if (pHandle1 != 0)
    {
        // Clear bit 0 and bit 31 of flags (offset 0x0c) - mark as released/invalid
        pHandle1[3] = pHandle1[3] & 0x7ffffffe;
        // Check if "needs update" flag (0x20000) is not set
        if ((pHandle1[3] & 0x20000) == 0)
        {
            // Set it to trigger update/removal
            pHandle1[3] = pHandle1[3] | 0x20000;
            // Notify system of object release
            onObjectReleased(); // FUN_0051b120
        }
        // Clear bit 18 (0x40000) from flags
        pHandle1[3] = pHandle1[3] & 0xfffbffff;
        // If there is an extra pointer at offset +0x08 of the handle block
        if (*(void***)(pHandle1 + 2) != (void**)0x0) // pHandle1[2] at offset 0x08
        {
            // Nullify the pointed-to data and clear the pointer
            ** (void***)(pHandle1 + 2) = 0;
            *(void***)(pHandle1 + 2) = 0;
        }
    }

    // Second handle at this+0x0c
    int* pHandle2 = *(int**)(this + 0xc);
    if (pHandle2 != 0)
    {
        pHandle2[3] = pHandle2[3] & 0x7ffffffe;
        if ((pHandle2[3] & 0x20000) == 0)
        {
            pHandle2[3] = pHandle2[3] | 0x20000;
            onObjectReleased(); // FUN_0051b120
        }
        pHandle2[3] = pHandle2[3] & 0xfffbffff;
        if (*(void***)(pHandle2 + 2) != (void**)0x0)
        {
            ** (void***)(pHandle2 + 2) = 0;
            *(void***)(pHandle2 + 2) = 0;
        }
    }
}