// FUNC_NAME: EventQueue::insertEvent
// Address: 0x00635f60
// Inserts a new event pair into the dynamic array at the position pointed to by pInsertPos.
// The event data is sourced from either a singleton (if key is 5 or 7) or a global default.
// The array grows if needed, with a header of 0xA8 bytes.

void __thiscall EventQueue::insertEvent(int *pInsertPos)
{
    int *pSource;
    int oldBase;
    int *pTop;
    int *pCur;
    int oldSize;
    int newSize;
    int newBase;

    // Determine source based on the key (first int of the insertion point)
    if (*pInsertPos == 5 || *pInsertPos == 7) {
        pSource = (int *)getEventSource(); // FUN_00637f90
    } else {
        pSource = &g_defaultEvent; // DAT_00e2a93c
    }

    oldBase = *(int *)(this + 0x1c); // m_base

    // If the source key is not 6, acquire a lock (mutex)
    if (*pSource != 6) {
        acquireLock(&g_eventLock); // FUN_006336f0
    }

    // Shift elements from the current top down to the insertion point to make room
    pTop = *(int **)(this + 8); // m_top
    for (pCur = pTop; pInsertPos < pCur; pCur -= 2) {
        *pCur = pCur[-2];
        pCur[1] = pCur[-1];
    }

    // Check if we need to grow the array (remaining space < 9 bytes? Actually < 9 slots? but 9 bytes is odd)
    if (*(int *)(this + 0x18) - *(int *)(this + 8) < 9) { // m_capacity - m_top < 9
        oldSize = *(int *)(this + 0x20); // m_size (number of slots)
        newSize = oldSize * 2;
        if (oldSize < 1) {
            newSize = oldSize + 0x15; // minimum growth of 21 slots
        }
        // Reallocate: old size = oldSize * 8 bytes, new size = newSize * 8 bytes
        newBase = reallocArray(oldSize * 8, newSize * 8); // FUN_006279a0
        *(int *)(this + 0x1c) = newBase; // m_base
        // New capacity = base + (newSize * 8 - 0xA8)  (0xA8 is header size)
        *(int *)(this + 0x18) = newBase - 0xA8 + newSize * 8; // m_capacity
        *(int *)(this + 0x20) = newSize; // m_size
        copyArrayData(); // FUN_00635b50 (copies old data to new buffer)
    }

    // Update top pointer (increment by one slot = 8 bytes)
    *(int *)(this + 8) = *(int *)(this + 8) + 8; // m_top += 8

    // Adjust insertion point for possible relocation
    pInsertPos = (int *)((int)pInsertPos + (*(int *)(this + 0x1c) - oldBase));

    // Write the event pair from the source
    *pInsertPos = *pSource;
    pInsertPos[1] = pSource[1];
}