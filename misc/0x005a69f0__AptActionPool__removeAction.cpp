// FUNC_NAME: AptActionPool::removeAction
void AptActionPool::removeAction(uint* actionPtr) {
    // poolBase points to a global action pool (DAT_0119a9cc)
    // Pool layout: base[0x500] = head index, base[0x501] = tail index
    // Each action entry is 5 ints (0x14 bytes), pool has 256 entries
    int* poolBase = DAT_0119a9cc;
    int* currentEntry = (int*)poolBase[0x500]; // head
    int* tailEntry = (int*)poolBase[0x501];    // tail

    if (currentEntry == tailEntry) {
        return; // empty pool
    }

    while (true) {
        // Bound check: currentEntry must be >= &aActionPool[0]
        if (currentEntry < poolBase) {
            // Debug assertion: "pCur >= &aActionPool[0]"
        }
        // Bound check: currentEntry must be < &aActionPool[256]
        if (poolBase + 0x500 <= currentEntry) {
            // Debug assertion: "pCur < &aActionPool[ 256 ]"
        }

        // Check if slot is free (first int == 0) and matches actionPtr (fourth int)
        if (*currentEntry == 0 && (uint*)currentEntry[3] == actionPtr) {
            if (currentEntry < (int*)poolBase[0x501]) {
                // Action found, call destructor via function table based on action type
                int typeIndex = *actionPtr & 0x7FFF;
                void (*destructor)(uint*) = (void (*)(uint*))DAT_0103aee0[typeIndex];
                destructor(actionPtr);

                // Remove entry by shifting subsequent entries left by one (0x14 bytes)
                int shiftSize = ((poolBase[0x501] - (int)currentEntry) / 0x14 - 1) * 0x14;
                _memmove(currentEntry, currentEntry + 5, shiftSize);
                currentEntry = (int*)(poolBase[0x501] - 0x14);
                if (currentEntry < poolBase) {
                    currentEntry = poolBase + 0x4FB;
                }
                poolBase[0x501] = (int)currentEntry;
                return;
            }

            int* headEntry = (int*)poolBase[0x500];
            if (headEntry < currentEntry) {
                // Slot is in front of head, shift head forward
                int typeIndex = *actionPtr & 0x7FFF;
                void (*destructor)(uint*) = (void (*)(uint*))DAT_0103aee0[typeIndex];
                destructor(actionPtr);

                void* src = (void*)poolBase[0x500];
                int moveSize = (((int)currentEntry - (int)src) / 0x14) * 0x14;
                _memmove((void*)((int)src + 0x14), src, moveSize);
                currentEntry = (int*)(poolBase[0x500] + 0x14);
                if (currentEntry == poolBase + 0x500) {
                    currentEntry = poolBase;
                }
                poolBase[0x500] = (int)currentEntry;
                return;
            }

            if (currentEntry == headEntry) {
                // Remove from head, advance head
                currentEntry = headEntry + 5;
                if (currentEntry == poolBase + 0x500) {
                    currentEntry = poolBase;
                }
                poolBase[0x500] = (int)currentEntry;
                return;
            }

            // Should not reach here
            // Debug assertion: "0"
        }

        // Advance to next entry
        currentEntry += 5;
        if (currentEntry == poolBase + 0x500) {
            currentEntry = poolBase; // wrap around
        }

        if (currentEntry == (int*)poolBase[0x501]) {
            return; // reached tail, not found
        }
    }
}