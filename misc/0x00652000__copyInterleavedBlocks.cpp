// FUNC_NAME: copyInterleavedBlocks
void __thiscall copyInterleavedBlocks(uint param1, int param2, void *param3, uint param4, int param5, undefined4 param6)
// Parameters:
//   param1 (in EAX) - source start pointer
//   param2 - source end pointer (exclusive)
//   param3 - destination buffer
//   param4 - block size in 4-byte units
//   param5 - total count of these units remaining; used for loop control
//   param6 - unknown (possibly flags for the helper call)
{
    void *pvVar1;
    rsize_t dstSize;
    uint uVar2;
    void *in_EAX;
    int iVar3;
    void *srcPtr;
    undefined4 local_4;

    uVar2 = param4;  // save original block size
    srcPtr = in_EAX;   // source pointer (passed in EAX per __thiscall convention)
    local_4 = param1;  // first parameter as flags (low byte cleared later)

    // Loop over pairs of blocks: while at least 2 blocks remain in source
    if ((int)(param4 * 2) <= param5) {
        do {
            // Compute pointers to the next two consecutive blocks (each block = param4 * 4 bytes)
            pvVar1 = (void *)((int)in_EAX + param4 * 4);
            srcPtr = (void *)((int)pvVar1 + param4 * 4);

            // Clear the low byte of the flags (alignment mask?)
            local_4 = local_4 & 0xffffff00;

            // Call helper to copy/transform two blocks to destination
            FUN_00652520(pvVar1, srcPtr, param3, param6, param4, local_4);

            // Advance destination by total bytes copied (sum of both blocks → 8 * param4 bytes)
            param3 = (void *)((int)param3 +
                              (((int)srcPtr - (int)pvVar1 >> 2) + ((int)pvVar1 - (int)in_EAX >> 2)) * 4);

            param5 = param5 + param4 * -2;   // consume 2 blocks
            in_EAX = srcPtr;                 // advance source pointer
        } while ((int)(param4 * 2) <= param5);
    }

    // Handle remaining partial block
    if ((int)param4 < param5) {
        // One more full block remains; use original block size and call helper with the remainder source
        param4 = param4 & 0xffffff00;
        FUN_00652520((void *)((int)srcPtr + uVar2 * 4), param2, param3, param6, param4, param4);
    }
    else {
        // Less than a block left: just memmove the remaining bytes
        iVar3 = param2 - (int)srcPtr >> 2;   // number of 4-byte words remaining
        if (0 < iVar3) {
            dstSize = iVar3 * 4;
            _memmove_s(param3, dstSize, srcPtr, dstSize);
            return;
        }
    }
    return;
}