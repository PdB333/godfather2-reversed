// FUNC_NAME: compareEntryPair
// Function at 0x00865880: Compares two entries from an array at this+0x70 with stride 0xc.
// Each entry: [0] = pointer/ID, [8] = pointer/ID (second field?).
// Returns 1 if either entry is null, else result of inner comparison (likely 0 or 1).
int compareEntryPair(int indexA, int indexB, void* object) {
    int* slotA = (int*)((char*)object + 0x70 + indexA * 0xc);
    int* slotB = (int*)((char*)object + 0x70 + indexB * 0xc);

    int valA = *slotA;
    if (valA == 0) {
        return 1;
    }

    int valB = *slotB;
    if (valB == 0) {
        return 1;
    }

    // Delegate to the actual comparison function using the two values from each slot.
    return FUN_008628e0(valA, slotA[2], valB, slotB[2]);
}