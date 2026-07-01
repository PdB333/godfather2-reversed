// FUNC_NAME: EventScheduler::addEvent
void __thiscall EventScheduler::addEvent(int thisPtr, int eventData)
{
    // +0x50: count of active events (must be < 20 to allocate)
    if (*(uint *)(thisPtr + 0x50) < 20) {
        // +0x44: head of free event list
        // +0x40: maybe a pointer to unallocated pool or supply
        // +0x34: flags (bit 0: allow allocation even if free list empty?)
        if (*(int *)(thisPtr + 0x44) == 0 &&
            (*(int *)(thisPtr + 0x40) == 0 || (*(byte *)(thisPtr + 0x34) & 1) == 0)) {
            // If free list empty and not allowed to expand, call error handler
            FUN_004de190();
        }
        // Pop free node
        int **freeNodePtr = *(int ***)(thisPtr + 0x44);
        if (freeNodePtr != (int **)0x0) {
            int *nextNode = *freeNodePtr; // linked list next
            *(int *)(thisPtr + 0x20) = *(int *)(thisPtr + 0x20) + 1; // likely total allocated count
            *(int *)(thisPtr + 0x1c) = *(int *)(thisPtr + 0x1c) - 1; // free count
            *(int **)(thisPtr + 0x44) = (int *)nextNode; // update head

            // Initialize free node as an event
            *freeNodePtr = 0;             // +0x00: next = null
            freeNodePtr[1] = 0;           // +0x04: unknown
            freeNodePtr[2] = 4;           // +0x08: type/size = 4
            *(short *)(freeNodePtr + 4) = 1;          // +0x10: state/status = 1 (active)
            *(short *)((int)freeNodePtr + 0x12) = 0;  // +0x12: unknown flag = 0
            *(short *)(freeNodePtr + 5) = 15000;      // +0x14: duration/delay (ms)
            freeNodePtr[6] = 0;           // +0x18: unknown
            freeNodePtr[7] = 0;           // +0x1C: unknown
            freeNodePtr[8] = eventData;   // +0x20: callback data
            freeNodePtr[3] = DAT_01205224 + 12000;    // +0x0C: scheduled time = current time + 12s

            // Call initializer/activator on the event node
            FUN_0093e4c0(freeNodePtr);
        }
    }
}