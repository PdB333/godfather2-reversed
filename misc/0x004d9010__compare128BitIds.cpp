// FUNC_NAME: compare128BitIds
bool __cdecl compare128BitIds(void* ptrA, void* ptrB)
{
    // If same object, return false (not less)
    if (ptrA == ptrB) {
        return false;
    }

    // Get pointers to the 128-bit data (4 x uint32) from each ID object
    uint* dataA = (uint*)getIdData(ptrA);
    uint* dataB = (uint*)getIdData(ptrB);

    // Lexicographic comparison of the 4 dwords (little-endian 128-bit)
    if (*dataB < *dataA) {
        return true;
    }
    if (*dataB <= *dataA) {
        if (dataB[1] < dataA[1]) {
            return true;
        }
        if (dataB[1] <= dataA[1]) {
            if (dataB[2] < dataA[2]) {
                return true;
            }
            if (dataB[2] <= dataA[2]) {
                return dataB[3] < dataA[3];
            }
        }
    }
    return false;
}