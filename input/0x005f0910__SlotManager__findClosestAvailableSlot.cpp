// FUNC_NAME: SlotManager::findClosestAvailableSlot
// Address: 0x005f0910
// Iterates over an array of slots (35 entries, each 16 bytes) starting at this+0x18.
// Finds the first available slot with a value >= given threshold and smallest difference.
// Marking occurs by setting a byte at offset +3 from the previous slot's fourth int? Unclear but preserved as decompiled.

void SlotManager::findClosestAvailableSlot(int thisPtr, int threshold) {
    int* currentSlot = (int*)(thisPtr + 0x18); // +0x18: start of slot array
    int bestDiff = 0x7fffffff;
    int* bestCandidate = nullptr;
    int* prevCandidate = nullptr;

    for (int i = 0; i < 35; i++) {
        int* candidate = prevCandidate;

        // Check if slot is free (byte at offset +0x08 from slot start is zero)
        if (*(char*)(currentSlot + 2) == '\0') { // currentSlot+2 = third int, low byte at +0x08
            candidate = currentSlot - 1; // pointer to previous slot's fourth int? 
            // If global flag at this+0x258 is zero, abort search
            if (*(char*)(thisPtr + 600) == '\0') {
                break;
            }
            candidate = prevCandidate; // revert
            // Check if slot's value >= threshold and difference is smaller
            if (threshold <= *currentSlot) {
                int diff = *currentSlot - threshold;
                if (diff < bestDiff) {
                    bestCandidate = currentSlot - 1; // store pointer to previous slot's fourth int
                    bestDiff = diff;
                }
            }
        }
        currentSlot += 4; // advance 16 bytes (4 ints)
        prevCandidate = candidate;
    }

    // Mark selected slot (set byte at offset +3 from bestCandidate)
    if (bestCandidate != nullptr) {
        *(char*)(bestCandidate + 3) = 1;
    }
}