// FUNC_NAME: PairTable::addEntry
void PairTable::addEntry(int* param_1)
{
    // param_1 points to a pair of 32-bit values: param_1[0] = first, param_1[1] = second
    int* arrayPtr;
    int count;
    uint index;
    int* entryPtr;

    // Global variables: 
    // DAT_0112db88 = pointer to array of pairs (each pair 8 bytes: first, second)
    // DAT_0112db8c = current number of entries
    // DAT_0112db90 = capacity of array (maximum entries before resize)
    count = PairTable::s_count; // DAT_0112db8c
    if (count != 0) {
        entryPtr = PairTable::s_array + 1; // +4 bytes to point to second element of first entry
        index = 0;
        do {
            if (*entryPtr == param_1[1]) {
                return; // duplicate second element found, no insertion
            }
            index = index + 1;
            entryPtr = entryPtr + 2; // advance to next pair (skip first, then second)
        } while (index < count);
    }

    // Check if resize needed
    if (count == PairTable::s_capacity) {
        int newCapacity;
        newCapacity = PairTable::s_capacity * 2;
        if (PairTable::s_capacity == 0) {
            newCapacity = 1;
        }
        PairTable::resizeArray(newCapacity); // FUN_008273d0
    }

    // Append new pair at end
    int* dest = PairTable::s_array + count * 2; // each pair 2 ints
    PairTable::s_count = count + 1;
    if (dest != nullptr) {
        *dest = param_1[0];
        dest[1] = param_1[1];
    }
    return;
}