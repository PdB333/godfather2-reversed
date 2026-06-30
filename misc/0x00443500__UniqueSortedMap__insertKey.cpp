// FUNC_NAME: UniqueSortedMap::insertKey
// Address: 0x00443500
// Role: Insert a key into a sorted associative array if not already present, returning pointer to the value slot.
// The structure at +0x00 has a pointer to an array of uint32 pairs (key, value), and +0x04 the count of pairs.
// The array is assumed to be sorted in ascending key order. Linear insertion point is found by scanning.
// If key is duplicate, returns nullptr. Otherwise allocates a new slot via internal function and returns &slot[1].

#include <cstdint>

// Forward declaration for internal allocation helper (address 0x00443a70)
uint32_t* AllocateSlot();

class UniqueSortedMap {
public:
    // Offset 0x00: pointer to array of pairs (each pair: key, value, 8 bytes)
    uint32_t* m_pPairs;
    // Offset 0x04: number of pairs currently in the array
    uint32_t   m_count;
    // (potential capacity/count, layout may include more fields)

    // Returns pointer to the value part of the inserted pair, or nullptr if key already exists.
    uint32_t* insertKey(uint32_t* pKey) {
        int32_t idx = 0; // current comparison index
        if (m_count > 0) {
            uint32_t* pEntry = m_pPairs;
            do {
                // Check for duplicate
                if (*pKey == pEntry[0]) {
                    return nullptr;
                }
                // Stop if key is smaller than current entry's key (insertion point found)
                if (*pKey < pEntry[0]) {
                    break;
                }
                idx++;
                pEntry += 2; // advance to next pair
            } while (idx < m_count);
        }

        // Allocate space for a new pair (key + value)
        uint32_t* pNewSlot = AllocateSlot(); // returns pointer to the key field of the new pair
        pNewSlot[0] = *pKey; // store the key
        return pNewSlot + 1; // return pointer to the value field
    }
};