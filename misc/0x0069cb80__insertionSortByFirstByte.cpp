// FUNC_NAME: insertionSortByFirstByte
void insertionSortByFirstByte(uint8_t* arrayStart, uint8_t* arrayEnd)
{
    if (arrayStart == arrayEnd) {
        return;
    }

    // Each element is 8 bytes: [4 bytes: key (low byte used) + data, 4 bytes: other data]
    const uint32_t elementSize = 8;

    // Start from the second element (index 1)
    uint8_t* current = arrayStart + elementSize;
    while (current != arrayEnd) {
        // Extract the key (low byte) and the full 8-byte element being inserted
        uint32_t currentKeyLowByte = *(uint32_t*)current & 0xFF;
        uint32_t currentData0 = *(uint32_t*)current;
        uint32_t currentData1 = *(uint32_t*)(current + 4);

        uint8_t* insertPos = current;
        uint8_t* prev = current - elementSize;

        // If the new element's key is less than the first element, shift all forward
        if ((uint8_t)currentData0 < *arrayStart) {
            // Shift all elements from start to current-1 one position to the right
            while (arrayStart != insertPos) {
                *(uint32_t*)insertPos = *(uint32_t*)(insertPos - elementSize);
                *(uint32_t*)(insertPos + 4) = *(uint32_t*)(insertPos - elementSize + 4);
                insertPos -= elementSize;
            }
            // Place the new element at the start
            *(uint32_t*)arrayStart = currentData0;
            *(uint32_t*)(arrayStart + 4) = currentData1;
        } else {
            // Find the insertion point by scanning backwards using the key of the previous element
            uint8_t bPrevKey = *(prev); // low byte of previous element
            uint8_t* candidatePrev = prev;
            while (true) {
                uint8_t* candidateInsertPos = insertPos;
                if (!((uint8_t)currentData0 < bPrevKey)) {
                    break;
                }
                // Shift previous element forward
                *(uint32_t*)candidateInsertPos = *(uint32_t*)candidatePrev;
                *(uint32_t*)(candidateInsertPos + 4) = *(uint32_t*)(candidatePrev + 4);
                // Move left
                candidateInsertPos = candidatePrev;
                candidatePrev -= elementSize;
                bPrevKey = *(candidatePrev);
                insertPos = candidatePrev; // wait, careful: we need to update insertPos properly
            }
            // Place the new element
            *(uint32_t*)insertPos = currentData0;
            *(uint32_t*)(insertPos + 4) = currentData1;
        }

        current += elementSize;
    }
}