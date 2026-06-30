// FUNC_NAME: ObjectSlotManager::setSlotDataByPointer
// Address: 0x005e2230
// Searches an array of 5 structures (each 0x4A4 bytes) starting at this+0x4 for a slot whose
// first pointer field (at slot start + 0x48C) matches targetPtr. If found, sets the value at
// slot + 0x248 to newValue. Returns 1 on success, 0 on failure (including targetPtr==0).

int __thiscall ObjectSlotManager::setSlotDataByPointer(void* this, void* targetPtr, int newValue)
{
    int slotIdx;
    int* slotPtr;
    int result = 0;

    if (targetPtr != 0) {
        slotIdx = 0;
        slotPtr = (int*)((char*)this + 0x490);          // +0x490: array of int pointers (5 entries spaced by 0x4A4)
        while (targetPtr != *slotPtr) {
            slotIdx = slotIdx + 1;
            slotPtr = slotPtr + 0x129;                    // advance 0x129 ints = 0x4A4 bytes
            if (4 < slotIdx) {
                return 0;
            }
        }
        // slotIdx found; compute base of the matching structure
        char* structureBase = (char*)this + 4 + slotIdx * 0x4A4;   // structure start at this+4 + slot*0x4A4
        if (structureBase != 0) {
            result = 1;
            *(int*)(structureBase + 0x248) = newValue;   // +0x248: field to set (e.g., squad assignment)
        }
    }
    return result;
}