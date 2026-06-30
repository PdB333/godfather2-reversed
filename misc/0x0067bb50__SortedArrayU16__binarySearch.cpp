// FUNC_NAME: SortedArrayU16::binarySearch
// Address: 0x0067bb50
// Searches an array of 8-byte elements sorted by the first uint16 key.
// Returns a combined uint: low byte 1 if found, else 0; high 24 bits are (lastMid & 0xFFFFFF00).
// On match, writes found index to outIndex.

uint SortedArrayU16::binarySearch(uint16 key, uint16* outIndex) const {
    int low = 0;
    int high = *(int16*)((uint8*)this + 0x108) - 1; // elementCount - 1, stored as short at +0x108

    if (high < 0) {
        // No elements; return 0
        return 0;
    }

    uint8* arrayBase = *(uint8**)((uint8*)this + 0xC); // pointer to array of 8-byte entries
    int mid = 0;

    while (low <= high) {
        mid = (low + high) / 2;
        uint16 val = *(uint16*)(arrayBase + mid * 8); // key field at offset 0 of each entry

        if (key == val) {
            *outIndex = (uint16)mid;
            return (uint)(mid << 8) >> 8 | 1; // ((uint32)mid & 0xFFFFFF00) | 1
        } else if (val <= key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    // Not found; return last mid with low byte zeroed
    return (uint32)mid & 0xFFFFFF00;
}