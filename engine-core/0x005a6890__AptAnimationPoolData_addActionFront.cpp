// Xbox PDB: AptAnimationPoolData::addActionFront
// FUNC_NAME: EventQueue::pushEvent
void EventQueue::pushEvent(int param_3, void* param_1, void* param_2) {
    uint* pWritePtr = (uint*)(g_eventQueueBase + 0x1400); // +0x1400: write pointer storage
    uint newWritePtr = *pWritePtr - 0x14; // Back up one entry (each entry is 0x14 bytes)

    // Wrap around if below buffer base
    if (newWritePtr < g_eventQueueBase) {
        newWritePtr = g_eventQueueBase + 0x13EC; // Last entry start
    }

    // Only write if buffer not full (write != read)
    if (newWritePtr != *(uint*)(g_eventQueueBase + 0x1404)) { // +0x1404: read pointer
        bool bWrap = (newWritePtr < g_eventQueueBase);
        *pWritePtr = newWritePtr; // Update write pointer

        if (bWrap) {
            FUN_0059bf00(); // Likely buffer overflow handler
        }
        if (pWritePtr <= (uint*)*pWritePtr) {
            FUN_0059bf00(); // Consistency check
        }

        // Write event entry at the new pointer
        *(uint*)newWritePtr = 1;                         // +0x00: event type/ID (fixed to 1)
        *(int*)(newWritePtr + 4) = param_3;             // +0x04: argument
        *(void**)(newWritePtr + 8) = param_1;           // +0x08: first object pointer
        uint* obj1 = *(uint**)(newWritePtr + 8);
        if (obj1 != DAT_0119cbbc) {
            uint flags = *obj1 & 0x7FFF;
            if (flags != 0x19 &&
                (((~(byte)(*obj1 >> 0xF) & 1) != 0 ||
                  (flags != 0xB && flags != 0x18 && flags != 0x17)))) {
                FUN_0059c230(obj1); // Possibly retain/addRef
            }
        }

        *(void**)(newWritePtr + 0xC) = param_2;         // +0x0C: second object pointer
        uint* obj2 = *(uint**)(newWritePtr + 0xC);
        if (obj2 != DAT_0119cbbc) {
            uint flags = *obj2 & 0x7FFF;
            if (flags != 0x19 &&
                (((~(byte)(*obj2 >> 0xF) & 1) != 0 ||
                  (flags != 0xB && flags != 0x18 && flags != 0x17)))) {
                FUN_0059c230(obj2); // Possibly retain/addRef
            }
        }

        *(int*)(newWritePtr + 0x10) = 0;                // +0x10: extra field (zero)
    }
}