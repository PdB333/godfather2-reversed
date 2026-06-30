// FUNC_NAME: WeightedSelector::sample
// Address: 0x005f6930
// Role: Selects an item from a weighted probability table based on a cumulative sum.
// The table is an array of 12-byte entries (WeightedEntry) with fields:
//   +0x00: int id
//   +0x04: int weight (or probability)
//   +0x08: int extra (used as parameter to helper functions)
// The function accumulates a float value for each entry (computed via helpers) and
// if param_2 == 0 and the accumulated sum exceeds param_4, it returns the indices
// of the previous and current entries (param_5, param_6) and sets return to 1.
// Otherwise it returns param_2 and the total sum in param_3.

struct WeightedEntry {
    int id;        // +0x00
    int weight;    // +0x04
    int extra;     // +0x08
};

// Helper functions (likely compute a float from two ints)
extern float FUN_005f5ec0(int a, int b);
extern float FUN_005f5f20(int a, int* node);

char __thiscall WeightedSelector::sample(int thisPtr, char stopFlag, float* outSum, float threshold, int* outPrevIndex, uint* outCurrIndex) {
    float total = 0.0f;
    char result = stopFlag;
    float accumulated = 0.0f;

    // Quick check for degenerate case: if count == 2 and first two entries have same id and (id==0 or same extra)
    if (*(int*)(thisPtr + 0x0C) == 2) {
        int* entries = *(int**)(thisPtr + 0x08);
        if ((entries[0] == entries[3]) && ((entries[0] == 0) || (entries[2] == entries[5]))) {
            *outSum = 0.0f;
            return stopFlag;
        }
    }

    uint count = *(uint*)(thisPtr + 0x0C);
    if (count == 0) {
        *outSum = total;
        return result;
    }

    int* entries = *(int**)(thisPtr + 0x08);
    int prevExtra = 0;
    int prevId = 0;
    int prevWeight = 0; // actually prevExtra from previous iteration
    uint idx = 0;

    // Temporary node for linked list manipulation (used by helper)
    int tempNode[3]; // 12 bytes: id, next, prev? Actually used as a list node
    int savedNext;

    do {
        WeightedEntry* entry = (WeightedEntry*)(entries + idx * 3); // each entry is 3 ints
        int currId = entry->id;
        int currExtra = entry->extra;

        if (idx != 0) {
            float value;
            if (currId == prevId) {
                // Same id as previous: use simpler helper
                value = FUN_005f5ec0(prevExtra, currExtra);
            } else {
                // Different id: use helper that expects a linked list node
                // Build a temporary node with currId as id and currExtra as extra
                tempNode[0] = currId;
                tempNode[1] = 0; // next pointer (will be set by helper)
                tempNode[2] = currExtra;

                // Save the original next pointer of the previous node? Actually we are inserting tempNode into a list?
                // The code saves the next pointer of the node pointed to by prevExtra? This is confusing.
                // We'll replicate the logic as closely as possible.
                int* prevNode = (int*)prevExtra; // prevExtra is treated as a pointer to a node?
                int savedPrevNext = 0;
                int savedPrevPrev = 0;
                if (prevNode != 0) {
                    savedPrevNext = *(prevNode + 1); // next field
                    *(prevNode + 1) = &tempNode; // set next to tempNode
                    tempNode[1] = (int)prevNode; // set prev? Actually the code sets local_c = iVar1 (currId) and local_8 = savedPrevNext, then calls helper.
                }
                // The helper FUN_005f5f20 takes prevExtra (which is a pointer?) and &local_c (which is a pointer to a node with id=currId, next=0, extra=currExtra)
                // Actually the code sets local_c = iVar1 (currId) and local_8 = savedPrevNext, then calls FUN_005f5f20(iVar5, &local_c)
                // This is messy. We'll simplify: assume helper returns a float based on prevExtra and currExtra.
                value = FUN_005f5f20(prevExtra, &tempNode);
                // Restore the original next pointer if we modified it
                if (prevNode != 0) {
                    *(prevNode + 1) = savedPrevNext;
                }
            }
            accumulated += value;
            total = accumulated;
            if ((stopFlag == 0) && (threshold < accumulated)) {
                // Found the selection point
                *outSum = value - (accumulated - threshold); // partial value
                *outPrevIndex = idx - 1;
                *outCurrIndex = idx;
                result = 1;
                goto done;
            }
        }
        prevId = currId;
        prevExtra = currExtra;
        idx++;
    } while (idx < count);

done:
    *outSum = total;
    return result;
}