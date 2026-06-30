//FUNC_NAME: ArrayContainer::removeElement
// Address: 0x005696c0
// Role: Removes a pointer element from a dynamic array by value, using a global mutex for thread safety.
// The array is stored at offset 0x228 (array of pointers), count at 0x328.
// Removal is O(n) search, then O(1) swap with last element and decrement count.

#include <cstdint>

// Forward declarations for lock/unlock functions (likely mutex operations)
void lockMutex(uint32_t* mutex);
void unlockMutex();

// Global mutex used by this function (address 0x00e2cbe8)
uint32_t g_arrayMutex;

class ArrayContainer {
public:
    // Removes the first occurrence of 'element' from the array.
    // If found, replaces it with the last element and shrinks the count.
    void removeElement(void* element) {
        lockMutex(&g_arrayMutex);

        uint32_t count = *(uint32_t*)(this + 0x328);
        uint32_t i = 0;

        if (count != 0) {
            // Linear search for the element
            while (*(void**)(this + 0x228 + i * 4) != element) {
                i++;
                if (i >= count) {
                    unlockMutex();
                    return; // Element not found
                }
            }

            // If element is found and not the last one, swap with last
            if (i < count - 1) {
                // Copy last element into the removed slot
                // Array base is 0x228, last element is at 0x228 + (count-1)*4
                // Equivalent to using base 0x224 and index count
                *(void**)(this + 0x228 + i * 4) = *(void**)(this + 0x224 + count * 4);
            }

            // Decrement count
            *(uint32_t*)(this + 0x328) = count - 1;
        }

        unlockMutex();
    }
};