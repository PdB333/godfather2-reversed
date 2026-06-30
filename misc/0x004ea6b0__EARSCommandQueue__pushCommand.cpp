// FUNC_NAME: EARSCommandQueue::pushCommand
void __thiscall EARSCommandQueue::pushCommand(int commandHandle)
{
    int isWorkerThread;
    int *slotBase;
    int queuePtr;

    // Fetch thread-local storage (FS:[0x2c] -> TEB -> some worker flag)
    isWorkerThread = *(int *)(**(int **)(__readfsdword(0x2c) + 0x34) + 0x34);

    // Choose slot offset depending on thread: +0x4 (main) or +0x9c (worker) relative to 'this'
    slotBase = (int *)((uint)(isWorkerThread != 0) * 0x98 + 4 + this);

    // Push current slot onto stack (copy contents to next slot)
    slotBase[1] = *slotBase;

    if (0 < *slotBase) {
        // Copy two 64-bit data chunks from positions +0x8/+0x10 to +0x88/+0x90
        *(unsigned long long *)(slotBase + 0x22) = *(unsigned long long *)(slotBase + 2);
        *(unsigned long long *)(slotBase + 0x24) = *(unsigned long long *)(slotBase + 4);
    }

    *slotBase = 0; // Reset slot count

    // Select global command queue context (main or worker)
    if (isWorkerThread != 0) {
        queuePtr = DAT_012068e8;
    } else {
        queuePtr = DAT_01206880;
    }

    // Store command vtable pointer
    **(void ***)(queuePtr + 0x14) = &PTR_LAB_01124c20;
    *(int *)(queuePtr + 0x14) += 4; // Advance write pointer

    // Store thread indicator (0 = main, 1 = worker)
    **(unsigned int **)(queuePtr + 0x14) = (unsigned int)(isWorkerThread != 0);
    *(int *)(queuePtr + 0x14) += 4; // Advance write pointer

    // Dispatch command to the actual execution routine
    FUN_004ea560(this, commandHandle, 0, 0xffffffff, 0, 0, 2);

    return;
}