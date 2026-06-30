// FUNC_NAME: ObjectTable::findByID
// Function at 0x004baf60 - Searches a contiguous array of 0x34-byte objects for one matching a given ID at offset +8.
// Class fields: +0x00 (vtable), +0x04 (pointer to array), +0x08 (count of elements).
int __thiscall ObjectTable::findByID(int targetID) {
    uint i;
    byte* pElement;

    if (this->count != 0) {
        pElement = (byte*)this->pArray;
        for (i = 0; i < this->count; i++) {
            // Compare ID at offset +8 within each 0x34-byte structure
            if (*(int*)(pElement + 8) == targetID) {
                return (int)pElement; // Return pointer to matching object
            }
            pElement += 0x34; // Advance to next element
        }
    }
    return 0; // Not found
}