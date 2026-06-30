// FUNC_NAME: SortedKeyValueArray::insertKeyIfNotExists
// Function at 0x006b4d50: Inserts a key into a sorted array of (key, value) pairs if not already present.
// Returns pointer to the value slot for the key, or nullptr if the key already exists.
// The array is assumed to be sorted ascending by key.
// Structure:
//   +0x00: uint* arrayPtr   (points to pairs: [key0, val0, key1, val1, ...])
//   +0x04: int   count      (number of pairs currently stored)

#include <cstdint>

// Forward declaration of the internal allocation function (likely at 0x006b4540)
// Returns pointer to newly allocated slot at the given index after shifting.
uint* allocateSlotAt(int index);

class SortedKeyValueArray {
public:
    uint* arrayPtr;
    int   count;

    // Attempt to insert a key. Returns pointer to the value slot if inserted,
    // or nullptr if the key already exists.
    uint* insertKeyIfNotExists(uint key) {
        int i = 0;
        if (count > 0) {
            uint* current = arrayPtr;
            do {
                if (key == *current) {
                    // Key already present
                    return nullptr;
                }
                if (key < *current) {
                    // Insertion point found (key is less than current key)
                    break;
                }
                i++;
                current += 2; // Move to next pair (skip value)
            } while (i < count);
        }
        // Allocate a new slot at index 'i' (shifts elements right)
        uint* newSlot = allocateSlotAt(i);
        *newSlot = key;    // Write the key
        return newSlot + 1; // Return pointer to the value slot (to be filled by caller)
    }
};