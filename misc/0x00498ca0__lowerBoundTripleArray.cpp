// FUNC_NAME: lowerBoundTripleArray
// Address: 0x00498ca0
// Role: Binary search lower bound on a sorted array of 12-byte triplets (3 uint32).
// Returns pointer to the first element >= key (in lexicographic order of the 3 uints).
// Parameters:
//   begin - start of array
//   end   - one past last element (passed in EAX register)
//   key   - triplet to search for
// Note: EA's EARS engine uses a custom calling convention; EAX holds the end pointer.

uint* lowerBoundTripleArray(uint* begin, uint* end, const uint* key)
{
    int count = (end - begin) / 3;  // Each element is 3 uints (12 bytes)
    int step, half;
    uint* current;

    if (count <= 0)
        return begin;

    do {
        half = count / 2;
        current = begin + half * 3;  // Advance by half elements

        // Lexicographic comparison of triplets
        bool less = *current < key[0];
        if (*current == key[0]) {
            less = current[1] < key[1];
            if (current[1] == key[1])
                less = current[2] < key[2];
        }

        if (less) {
            begin = current + 3;  // Move past this element
            count = count - half - 1;
        } else {
            count = half;
        }
    } while (count > 0);

    return begin;
}