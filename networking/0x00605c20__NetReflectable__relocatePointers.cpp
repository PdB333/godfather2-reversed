// FUNC_NAME: NetReflectable::relocatePointers
void __thiscall NetReflectable::relocatePointers(byte* outWasRelocated)
{
    // Extract sign bit of the flag at +0x08 to indicate relocation status (0 = not yet, 1 = already done)
    *outWasRelocated = (byte)((uint32)(*(int32*)((uint8*)this + 0x08)) >> 31);

    // If the relative pointer at +0x0c is non-zero, convert it to an absolute address by adding this base
    if (*(int32*)((uint8*)this + 0x0c) != 0)
    {
        *(int32*)((uint8*)this + 0x0c) = (int32)this + *(int32*)((uint8*)this + 0x0c);
    }

    // Set +0x18 to point to the data area starting at offset +0x20
    *(int32*)((uint8*)this + 0x18) = (int32)this + 0x20;

    // If the count at +0x14 is non-zero, set +0x1c to point to the start of the second offset array
    // (located after the first array of size [count at +0x10] ints)
    if (*(int32*)((uint8*)this + 0x14) != 0)
    {
        *(int32*)((uint8*)this + 0x1c) = (int32)this + 0x20 + *(int32*)((uint8*)this + 0x10) * 4;
    }

    // Retrieve pointer to the relocation offset array
    int32* offsetArray = *(int32**)((uint8*)this + 0x1c);
    // Total number of offsets to fix: product of count at +0x10 and count at +0x14
    int32 numOffsets = *(int32*)((uint8*)this + 0x10) * *(int32*)((uint8*)this + 0x14);

    // Relocate each offset in the array by adding the base address
    for (int32 i = 0; i < numOffsets; i++)
    {
        offsetArray[i] = offsetArray[i] + (int32)this;
    }
}