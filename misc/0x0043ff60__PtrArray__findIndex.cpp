// FUNC_NAME: PtrArray::findIndex
// Address: 0x0043ff60
// Returns the index of `item` in the array, or 0xFFFFFFFF if not found.
// Assumes thisPtr->array is a valid pointer to an array of ints (pointers), and thisPtr->count is the number of elements.

#include <cstdint>

// Structure layout:
// +0x00: unknown (possibly vtable)
// +0x04: int* array
// +0x08: uint32_t count
struct PtrArray {
    int32_t* array;   // +0x04
    uint32_t count;   // +0x08
};

uint32_t __thiscall PtrArray::findIndex(PtrArray* thisPtr, int32_t item) {
    uint32_t result = 0xFFFFFFFF; // initial sentinel for not found

    if (item == 0) {              // null pointer check
        return result;
    }

    if (thisPtr->count != 0) {
        int32_t* current = thisPtr->array;
        uint32_t index = 0;
        while (*current != item) {
            index++;
            current++;
            if (index >= thisPtr->count) {
                return 0xFFFFFFFF; // not found
            }
        }
        result = index;
    }
    return result;
}