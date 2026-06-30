// FUNC_NAME: SortedIntArray::findValue

// 0x0068f700: Binary search in a sorted array of 32-bit values using a key computed from a range descriptor.
// The array base pointer is at this+0x10, and the element count at this+0x14 (each element is 4 bytes).
// param_2 points to a 4-integer structure (e.g., a rectangle or range) used to compute the search key.
// Returns the found value if present, or 0 if not found.

struct SearchResult {
    unsigned int* found;   // pointer to the matching element, or end if not found
    unsigned int* insert;  // insertion point (where element would be inserted)
};

unsigned int __thiscall SortedIntArray::findValue(int* rangeParams) {
    // Compute the search key from the range parameters
    // The formula suggests something like: key = computeKey(base + width, height + base + width)
    unsigned int key = computeKey(rangeParams[0] + rangeParams[2],
                                   rangeParams[3] + rangeParams[0] + rangeParams[2]);

    // Prepare a pointer to the key for the binary search comparator
    int* keyPtr = &key;

    // Perform binary search on the sorted array
    SearchResult result;
    binarySearch(&result,
                 *reinterpret_cast<unsigned int**>(this + 0x10),         // array start
                 *reinterpret_cast<unsigned int**>(this + 0x10) + *reinterpret_cast<int*>(this + 0x14), // array end (start + count)
                 &keyPtr,
                 elementComparator,     // callback at 0x0068e370
                 0);                    // flags

    // If found (not at end and not at insertion point), return the value
    if (result.found != *reinterpret_cast<unsigned int**>(this + 0x10) + *reinterpret_cast<int*>(this + 0x14) &&
        result.found != result.insert) {
        return *result.found;
    }
    return 0;
}