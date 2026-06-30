// FUNC_NAME: EARS::Framework::MapImpl::erase

#include <cstdint>
#include <cstddef>

// Context: This function removes an element from a map-like container.
// The container stores an array of key-value pairs at this+0xF0, with count at this+0xF4.
// Each pair is two consecutive pointers: first is key (typically an object pointer), second is value (or next?).
// param_2 is an iterator pointing to a node structure that contains the key at offset 0x48.
// The function searches for the matching key and removes it by index via FUN_006b3580 (likely shift remaining elements).
// Then it calls FUN_004daf90 on the stack variable to finalize the removal (possibly free node memory).

// Assumed structure layout for the container (this):
// +0xF0: pointer to array of pairs (each pair is 8 bytes: key, value)
// +0xF4: uint32_t elementCount

// Assumed structure layout for the iterator (param_2):
// If non-null, +0x48 contains the actual key pointer used for lookup.

// External helper functions:
void __thiscall FUN_006b3580(uint32_t index);   // Removes element at given index (shifts array)
void __thiscall FUN_004daf90(int* pNode);        // Likely releases the iterator node

void __thiscall MapImpl::erase(void* thisPtr, void* iterator) {
    int* nodeKeyPtr;          // Pointer to the key inside iterator
    int* keyArray;            // Pointer to current key in the array
    uint32_t i;               // Loop index
    int stackNode;            // Local copy of the key pointer (used in finalization)

    // Extract the key pointer from the iterator (offset +0x48)
    if (iterator == nullptr) {
        nodeKeyPtr = nullptr;
    } else {
        nodeKeyPtr = (int*)((uint8_t*)iterator + 0x48);
    }

    // Initialize local sentinel/stack structure for finalization
    // The code sets *(void**)(nodeKeyPtr + 4) = &stackNode; seems to create a linked list or mark for deletion.
    // We replicate this by storing the address of stackNode into the location after nodeKeyPtr.
    if (nodeKeyPtr != nullptr) {
        *(int**)((uint8_t*)nodeKeyPtr + 4) = &stackNode;   // This is suspicious: writing to nodeKeyPtr+4
    }

    // Search the array for the matching key
    i = 0;
    if (*(uint32_t*)((uint8_t*)thisPtr + 0xF4) != 0) {
        keyArray = *(int**)((uint8_t*)thisPtr + 0xF0);
        do {
            if (*keyArray == nodeKeyPtr) {       // Compare key pointer in array with target
                if (i < 0x80000000) {            // Check if index is valid (assuming signed comparison)
                    FUN_006b3580(i);             // Remove element at index i
                }
                break;
            }
            i++;
            keyArray += 2;                       // Move to next pair (skip value pointer)
        } while (i < *(uint32_t*)((uint8_t*)thisPtr + 0xF4));
    }

    // Finalize removal: if nodeKeyPtr was not null, call cleanup function
    if (nodeKeyPtr != nullptr) {
        FUN_004daf90(&stackNode);               // Pass address of local variable (stackNode)
    }
    return;
}