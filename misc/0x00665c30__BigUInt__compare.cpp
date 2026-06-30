// FUNC_NAME: BigUInt::compare
// Function address: 0x00665c30
// Purpose: Lexicographic comparison of two big-endian unsigned integer arrays.
// The objects have a length field at +0x00 and a pointer to the data array at +0x0C.
// Returns -1 if this < other, 0 if equal, 1 if this > other.

struct BigUInt {
    int   length;      // +0x00: number of uint32 elements in the array
    int   field_4;     // +0x04: unknown (not used in comparison)
    int   field_8;     // +0x08: unknown (not used in comparison)
    uint* data;        // +0x0C: pointer to array of uint32 (most significant first)
};

int __fastcall BigUInt::compare(BigUInt* other) {
    int cmpLen = this->length;
    int otherLen = other->length;

    // Compare lengths first
    if (otherLen < cmpLen) {
        return 1;
    }
    if (cmpLen < otherLen) {
        return -1;
    }

    // Compare elements from most significant to least (reverse order)
    uint* thisData = this->data + cmpLen - 1;
    uint* otherData = other->data + cmpLen - 1;
    for (int i = 0; i < cmpLen; i++) {
        uint a = *thisData;
        uint b = *otherData;
        if (a > b) {
            return 1;
        }
        if (a < b) {
            return -1;
        }
        thisData--;
        otherData--;
    }
    return 0;
}