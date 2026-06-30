// FUNC_NAME: DeferredDeleteQueue::processDeletions
void __fastcall DeferredDeleteQueue::processDeletions(int param_1) // this in ecx
{
    int remaining = *(int *)(param_1 + 0x24); // +0x24: count of pending deletions
    while (remaining != 0)
    {
        // entry is 8 bytes; read first 4 as handle
        uint32_t handle = *(uint32_t *)(*(int *)(param_1 + 0x18) + *(int *)(param_1 + 0x20) * 8);
        // +0x18: base pointer to ring buffer
        // +0x20: current read index (0-based)
        // each entry is 8 bytes

        int newIndex = *(int *)(param_1 + 0x20) + 1;
        *(int *)(param_1 + 0x20) = newIndex; // +0x20: increment read index

        if (*(int *)(param_1 + 0x1C) <= newIndex) // +0x1C: max number of entries (buffer size)
        {
            *(int *)(param_1 + 0x20) = 0; // wrap around
        }

        *(int *)(param_1 + 0x24) = remaining - 1; // decrement count
        FUN_0044a0e0(handle); // release the resource identified by handle

        remaining = *(int *)(param_1 + 0x24); // re-read count
    }
}