// FUNC_NAME: SortedArray::insert
// Function at 0x006bb940: Inserts an element into a sorted dynamic array, maintaining order by a key at offset +0x5c of each element.
// If duplicate keys exist, insertion position is randomized within the group of equal keys.
// The calling convention is __thiscall.

#include <cstdint>
#include <cmath>
#include <cstdlib> // for rand? but using global table

// Forward declaration of the helper that inserts a slot at a given index and returns a pointer to the new slot.
extern int* InsertSlotAtIndex(int index);

// Assumed external random-related globals
extern uint32_t g_randomMask; // DAT_010c2678
extern uint32_t g_randomCounter; // DAT_012054b4, incremented each call
extern float g_randomFloats[]; // table starting at DAT_010c2680

// The class containing a dynamic array of pointers sorted by a key from each pointed object.
class SortedArray {
public:
    // Offsets from decompiled code:
    // +0x5c: int* mArray       // pointer to array of int (each int is a pointer to some object)
    // +0x60: uint32_t mCount   // number of elements currently stored

    int* mArray;        // actually a pointer to an array of ints (each int is a pointer to an object)
    uint32_t mCount;

    // Insert an element (pointer) into the sorted array.
    // param_2 is the pointer to the object to insert.
    void insert(int* element) {
        uint32_t count = mCount;
        uint32_t existingIdx = 0;

        // Check if element already exists in the array (by pointer identity)
        if (count != 0) {
            int* arrayPtr = mArray;
            do {
                if (arrayPtr[existingIdx] == reinterpret_cast<int>(element)) {
                    // Duplicate found; early return (the original code returns if uVar3 >= 0, which is always true)
                    return;
                }
                existingIdx++;
                arrayPtr++;
            } while (existingIdx < count);
        }

        // Find insertion point based on the sort key (at offset +0x5c of the pointed object)
        // The sort key is a uint32_t at element + 0x5c.
        uint32_t key = *(reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(element) + 0x5c));

        uint32_t firstEqualIdx = 0xffffffff; // uVar4
        uint32_t insertIdx = count;          // uVar3, default to end
        uint32_t currentIdx = 0;             // uVar5
        uint32_t remainingCount = count;     // uVar1

        if (count != 0) {
            int* arrayPtr = mArray;
            do {
                uint32_t existingKey = *(reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(arrayPtr[currentIdx]) + 0x5c));
                if (key == existingKey) {
                    // First occurrence of equal key
                    if (firstEqualIdx == 0xffffffff) {
                        firstEqualIdx = currentIdx;
                    }
                } else {
                    // Key differs: update insertIdx to current position
                    insertIdx = currentIdx;
                    if (key < existingKey) {
                        // Should insert before this element
                        break;
                    }
                }
                currentIdx++;
                arrayPtr++;
                remainingCount = count; // reset counter (not really needed)
            } while (currentIdx < count);
            // insertIdx is now the first index where key < existingKey (or count if none)
        }

        if (firstEqualIdx != 0xffffffff) {
            // There are elements with equal key. Insert at a random position within the equal-key group.
            // Compute random index between firstEqualIdx and insertIdx (inclusive of insertIdx? original code uses +1 to include).
            uint32_t rangeSize = (insertIdx - firstEqualIdx) + 1; // number of possible positions

            // Generate random float from table and round
            uint32_t randIndex = g_randomMask & g_randomCounter;
            g_randomCounter++;
            float randomFloat = g_randomFloats[randIndex];
            int randOffset = static_cast<int>(std::round(randomFloat * static_cast<float>(rangeSize)));
            int actualIndex = randOffset + static_cast<int>(firstEqualIdx);

            int* slot = InsertSlotAtIndex(actualIndex);
            *slot = reinterpret_cast<int>(element);
        } else {
            // No equal key: insert at the sorted position (or at end if key is largest)
            int* slot = InsertSlotAtIndex(static_cast<int>(insertIdx));
            *slot = reinterpret_cast<int>(element);
        }
    }
};