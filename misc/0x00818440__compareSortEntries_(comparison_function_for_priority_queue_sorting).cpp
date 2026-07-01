// FUNC_NAME: compareSortEntries (comparison function for priority queue sorting)
// Address: 0x00818440
// This function is used as a comparator to sort entries based on a byte priority at +0x11 of the pointed object,
// a float priority, and a flag bit.

struct SortEntry {
    void* object;      // +0x00: pointer to some object (e.g., action/behavior)
    float priority;    // +0x04: float priority value
    uint32_t flags;    // +0x08: flags (bit 0 used)
};

// Returns true if entry 'a' should come before entry 'b'
bool compareSortEntries(const SortEntry* a, const SortEntry* b) {
    uint32_t aFlag = a->flags & 1;
    uint32_t bFlag = b->flags & 1;

    // Default: a before b
    bool result = true;

    // This logic handles ordering when flags differ:
    // If (a has flag OR b does not have flag) AND (b has flag OR a does not have flag)
    // then we compare by object priority bytes and float priority.
    // Otherwise, if aFlag=1 and bFlag=0, a comes after b (result=false).
    // If aFlag=0 and bFlag=1, the outer condition fails and default (true) holds.
    if (aFlag || !bFlag) {
        if (bFlag || !aFlag) {
            // Both flags same (0,0 or 1,1): compare by object byte at +0x11, then float priority
            char aPriorityByte = *(char*)((uintptr_t)a->object + 0x11);
            char bPriorityByte = *(char*)((uintptr_t)b->object + 0x11);
            if (aPriorityByte < bPriorityByte) {
                return true;
            }
            if (aPriorityByte <= bPriorityByte && a->priority < b->priority) {
                return true;
            }
        }
        result = false;
    }
    return result;
}