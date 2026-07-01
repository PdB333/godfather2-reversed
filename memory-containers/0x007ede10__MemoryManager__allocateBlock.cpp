// FUNC_NAME: MemoryManager::allocateBlock
// Address: 0x007ede10
// This function implements a first-fit memory block allocation within a custom pool.
// Offsets: this+0x14 = allocationCount, this+0x18 = poolDescriptor, this+0x20 = some float (base?), this+0x38 = flags (bit0 = locked).
// The pool uses a linked list of free blocks; each block has [next] at offset 0 and [size] at offset 12 (0xC).

int __thiscall MemoryManager::allocateBlock(int uiSize, int param3, int param4, int param5)
{
    int iVar1;
    int iVar3;
    undefined4 *pFreeBlock;
    undefined4 *pCurrent;
    char buffer[12]; // local_28, local_24, local_20 (string buffer)
    unused_variable **pDestructor; // local_1c (might be for cleanup)
    int nRemainingSize; // local_18
    undefined4 *pCleanupThis; // local_14 (maybe for RAII)
    short sFlag; // local_a (uninitialized, used in loop)
    uint uLockFlag; // local_4 (bit flag)

    if ((*(byte *)(this + 0x38) & 1) != 0) {
        // Locked – skip allocation
        return 0;
    }

    // Check if the pool is full (last allocated block points to sentinel)
    if (*(int *)(this + 0x14) - 1 == *(int *)(*(int *)(this + 0x18) + 0x1c)) {
        // Log an error or debug message (DAT_0112bb48 is likely a string)
        buffer[0] = DAT_0112bb48;
        buffer[4] = 0;
        buffer[8] = 0;
        FUN_00408a00(buffer, 0); // probably prints/logs
    }

    if (DAT_0112a53c == 0) {
        // Some global flag prevents allocation
        return 0;
    }

    // Adjust size with a base offset (this+0x20 is a float)
    FUN_007ec2a0((int)(*(float *)(this + 0x20) + uiSize), param3, param4, param5);

    if (uiSize < 1) {
        // Allocate zero-size block – initialize a stub
        FUN_007ec450(&pDestructor);
    } else {
        iVar1 = *(int *)(this + 0x18);
        pCurrent = *(undefined4 **)(**(int **)(iVar1 + 0x18));
        while (true) {
            pFreeBlock = *(undefined4 **)(*(int *)(this + 0x18) + 0x18);
            if (iVar1 != *(int *)(this + 0x18)) {
                FUN_00b97aea(); // assert?
            }
            if (pCurrent == pFreeBlock) {
                // Reached end of list – allocate a new block
                iVar1 = *(int *)(*(int *)(this + 0x18) + 0x18);
                iVar3 = FUN_007ecb80(iVar1, *(undefined4 *)(iVar1 + 4), &pDestructor);
                FUN_007edbf0(1);
                *(int *)(iVar1 + 4) = iVar3;
                **(int **)(iVar3 + 4) = iVar3;
                goto LAB_007edf36;
            }
            if (pCurrent == *(undefined4 **)(iVar1 + 0x18)) {
                FUN_00b97aea(); // assert?
            }
            if (nRemainingSize <= (int)pCurrent[3]) {
                break; // Found a block big enough
            }
            nRemainingSize -= pCurrent[3];
            if (pCurrent == *(undefined4 **)(iVar1 + 0x18)) {
                FUN_00b97aea(); // assert?
            }
            pCurrent = (undefined4 *)*pCurrent; // advance to next block
        }
        // Split the found block
        pCurrent[3] = pCurrent[3] - nRemainingSize;
        FUN_007eddb0(&buffer, iVar1, pCurrent, &pDestructor);
LAB_007edf36:
        uLockFlag |= 1;
    }

    // Cleanup/destructor block
    pDestructor = &PTR_FUN_00d6ffac; // some destructor table
    while (sFlag != 0) {
        FUN_00408090(); // cleanup iterations
    }
    if ((pCleanupThis != (undefined4 *)0x0) && ((uLockFlag & 1) == 0)) {
        (*(code **)*pCleanupThis)(1);
    }
    return 1;
}