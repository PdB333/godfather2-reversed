// FUNC_NAME: rotateArray
// Address: 0x00652420
// Purpose: Rotates the elements in the range [start, end) so that the element pointed by newFirst becomes the new first.
// This is a generic rotate operation for arrays of 32-bit values, using the GCD-based cycle algorithm.

#include <cstdint>

void rotateArray(void* start, void* end, void* newFirst) {
    // Cast to 32-bit unsigned pointers for element access
    uint32_t* pStart = static_cast<uint32_t*>(start);
    uint32_t* pEnd = static_cast<uint32_t*>(end);
    uint32_t* pNewFirst = static_cast<uint32_t*>(newFirst);

    // Number of elements in the range
    int elemCount = pEnd - pStart;
    // Number of positions to rotate left (offset of newFirst from start)
    int rotateBy = pNewFirst - pStart;

    // Normalize rotateBy to [0, elemCount)
    rotateBy %= elemCount;
    if (rotateBy < 0) rotateBy += elemCount;

    // If no rotation needed, exit
    if (rotateBy == 0) return;

    // Compute GCD of elemCount and rotateBy using Euclidean algorithm
    int a = elemCount;
    int b = rotateBy;
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    int gcd = a;

    // Only proceed if GCD is less than the total length and positive
    if (gcd >= elemCount || gcd <= 0) return;

    // Rotate using cycles: for each cycle start, rotate elements around
    for (int i = 0; i < gcd; ++i) {
        uint32_t temp = pStart[i];
        int current = i;
        int next = (current + rotateBy) % elemCount;
        while (next != i) {
            pStart[current] = pStart[next];
            current = next;
            next = (current + rotateBy) % elemCount;
        }
        pStart[current] = temp;
    }
}