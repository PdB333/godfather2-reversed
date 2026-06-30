// FUNC_NAME: compareGUIDLessThan
#include <cstdint>

// Forward declaration of the function that extracts the GUID data pointer from an object
uint32_t* getGUIDData(void* object);

// Compares two GUID-like structures stored as four 32-bit integers.
// Returns true if the GUID pointed by b is lexicographically less than the GUID pointed by a.
bool compareGUIDLessThan(void* a, void* b) {
    uint32_t* guidDataA = getGUIDData(a);
    uint32_t* guidDataB = getGUIDData(b);

    // Compare the four 32-bit fields in order (big-endian or network byte order style)
    if (guidDataB[0] < guidDataA[0]) return true;
    if (guidDataB[0] > guidDataA[0]) return false;
    if (guidDataB[1] < guidDataA[1]) return true;
    if (guidDataB[1] > guidDataA[1]) return false;
    if (guidDataB[2] < guidDataA[2]) return true;
    if (guidDataB[2] > guidDataA[2]) return false;
    return guidDataB[3] < guidDataA[3];
}