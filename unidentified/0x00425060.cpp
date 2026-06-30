// FUN_NAME: DataArray::getEntry
void __thiscall DataArray::getEntry(int thisPtr, Vector3D* outVec, int slotIndex)
{
    // +0xe4 : bool m_useCache
    if (*(char*)(thisPtr + 0xe4) != 0)
    {
        // Use cached data from +0x130 (12 bytes)
        outVec->x = *(float*)(thisPtr + 0x130);
        outVec->y = *(float*)(thisPtr + 0x134);
        outVec->z = *(float*)(thisPtr + 0x138);
        return;
    }

    // Resolve slot index via external function
    int idx = resolveSlotIndex(slotIndex); // FUN_00424c90

    // Base pointer to array of structures (size 0x1d0 per entry) at +0x10
    int* base = *(int**)(thisPtr + 0x10);
    int entryOffset = idx * 0x1d0 + 0x20; // +0x20 offset to 12-byte data within each structure

    // Read the three 4-byte values (likely floats for position/vector)
    // Global temporary storage (DAT_01223d18 - 12 bytes)
    static float tempData[3]; // Equivalent to DAT_01223d18 / DAT_01223d20

    tempData[0] = *(float*)((int)base + entryOffset);
    tempData[1] = *(float*)((int)base + entryOffset + 4);
    tempData[2] = *(float*)((int)base + entryOffset + 8);

    // Copy into output structure
    outVec->x = tempData[0];
    outVec->y = tempData[1];
    outVec->z = tempData[2];
}