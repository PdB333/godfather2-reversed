// FUNC_NAME: RingBufferSearch::findMatchingElement
// Address: 0x00721d70
// Searches a circular buffer of elements (0x24 bytes each) for an element matching flags (param_2) and distance criteria.
// Returns pointer to the element if found, else 0.
// If param_5 != 0, continues scanning to find the element with the greatest distance (+0x0c) among matches.
// param_1: this pointer to ring buffer struct (size, head, tail, base)
// param_4: squared distance threshold (negative = no distance check)

int __thiscall RingBufferSearch::findMatchingElement(int *thisPtr, uint flags, float *position, float sqDistThresh, char bFindFarthest)
{
    int currentIndex;
    int bestElement;
    float bestDistance;
    int elementAddr;

    currentIndex = thisPtr[2];   // +0x08: current read index (tail)
    bestElement = 0;
    bestDistance = DAT_00d5ccf8; // global max distance (e.g., 1e30f)

    do {
        if (currentIndex == thisPtr[1]) { // +0x04: write index (head) -> buffer empty
            return bestElement;
        }
        elementAddr = thisPtr[3] + currentIndex * 0x24; // +0x0c: base address of element array
        // Check if element matches required flags (stored at +0x10)
        if ((*(uint *)(elementAddr + 0x10) & flags) != 0) {
            // If no distance check needed (sqDistThresh < 0 or position is null)
            if ((sqDistThresh < 0.0f) || (position == (float *)0x0)) {
                // If not finding farthest, or current element's distance > bestDistance, update candidate
                if ((bFindFarthest == '\0') || (bestDistance < *(float *)(elementAddr + 0x0c))) {
                    // Update best distance and element address
                    bestDistance = *(float *)(elementAddr + 0x0c);
                    bestElement = elementAddr;
                }
                // If not finding farthest, return immediately
                if (bFindFarthest == '\0') {
                    return bestElement;
                }
            } else {
                // Distance check: ensure element has a position (skip if pointer null)
                // Note: The decompiler shows a null check on the position field itself,
                // but this is likely a decompilation artifact. The original code probably checked
                // a pointer to a position vector stored in the element. For now we treat it as a simple position.
                // Actually, the condition (float *)(elementAddr + 0x14) == (float *)0x0 is always false
                // because elementAddr+0x14 is a valid address. This might be a misinterpration of
                // a pointer check. We'll assume it's checking something else, but for correctness we keep it.
                if ( ((float *)(elementAddr + 0x14) == (float *)0x0) || // check if position pointer is null (decompiler oddity)
                     ( (bFindFarthest != '\0') && (*(float *)(elementAddr + 0x0c) <= bestDistance) ) ||
                     ( ( *(float *)(elementAddr + 0x14) - *position ) * ( *(float *)(elementAddr + 0x14) - *position ) + 
                       ( *(float *)(elementAddr + 0x18) - position[1] ) * ( *(float *)(elementAddr + 0x18) - position[1] ) + 
                       ( *(float *)(elementAddr + 0x1c) - position[2] ) * ( *(float *)(elementAddr + 0x1c) - position[2] ) >= sqDistThresh * sqDistThresh ) ) {
                    // Skip this element (go to next iteration)
                } else {
                    // Element passes distance test -> update candidate
                    bestDistance = *(float *)(elementAddr + 0x0c);
                    bestElement = elementAddr;
                }
            }
        }
        // Circular increment of index
        currentIndex++;
        if (*thisPtr <= currentIndex) { // +0x00: buffer capacity
            currentIndex = 0;
        }
    } while (true);
}