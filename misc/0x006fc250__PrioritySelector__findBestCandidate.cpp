// FUNC_NAME: PrioritySelector::findBestCandidate
// Address: 0x006fc250
// Role: Iterates over 5 fixed priority entries (each 0x14 bytes) starting at offset 0x10.
//       Returns pointer to the active entry (sign bit clear) with the smallest priority value.
//       Returns 0 if no active entry.

int __fastcall PrioritySelector::findBestCandidate(PrioritySelector* this) {
    int bestOffset = 0;

    // Entry 0 at offset +0x10
    if (!(*(int*)((uint8_t*)this + 0x10) & 0x80000000)) {
        bestOffset = 0x10;
    }

    // Entry 1 at offset +0x24
    if (!(*(int*)((uint8_t*)this + 0x24) & 0x80000000)) {
        if (bestOffset == 0 || 
            (*(unsigned int*)((uint8_t*)this + 0x28) < *(unsigned int*)((uint8_t*)this + bestOffset + 4))) {
            bestOffset = 0x24;
        }
    }

    // Entry 2 at offset +0x38
    if (!(*(int*)((uint8_t*)this + 0x38) & 0x80000000)) {
        if (bestOffset == 0 || 
            (*(unsigned int*)((uint8_t*)this + 0x3c) < *(unsigned int*)((uint8_t*)this + bestOffset + 4))) {
            bestOffset = 0x38;
        }
    }

    // Entry 3 at offset +0x4c
    if (!(*(int*)((uint8_t*)this + 0x4c) & 0x80000000)) {
        if (bestOffset == 0 || 
            (*(unsigned int*)((uint8_t*)this + 0x50) < *(unsigned int*)((uint8_t*)this + bestOffset + 4))) {
            bestOffset = 0x4c;
        }
    }

    // Entry 4 at offset +0x60
    if (!(*(int*)((uint8_t*)this + 0x60) & 0x80000000)) {
        if (bestOffset == 0 || 
            (*(unsigned int*)((uint8_t*)this + 0x64) < *(unsigned int*)((uint8_t*)this + bestOffset + 4))) {
            bestOffset = 0x60;
        }
    }

    if (bestOffset == 0) {
        return 0;
    }
    return reinterpret_cast<int>((uint8_t*)this + bestOffset);
}