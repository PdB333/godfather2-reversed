// FUNC_NAME: SortedArray::insertUniqueValue
/**
 * Function at 0x00482c90
 * Assumes object passed in EAX (this) with structure:
 *   +0x00: uint* dataArray (pointer to sorted array of uint)
 *   +0x04: int32 count (number of elements in array)
 * Inserts the value *valuePtr into the array if not duplicate.
 * Returns pointer to the inserted element's data area (after the key), or NULL if duplicate.
 * Uses internal allocator FUN_00482ee0 to allocate memory for new node.
 * Nodes are presumably larger than one uint (allocated block -> store key, return pointer past key).
 */
#include <stdint.h>

// Forward declaration of internal allocator
uint32_t* allocateInsertNode();

uint32_t* SortedArray::insertUniqueValue(uint32_t* valuePtr) {
    int32_t i = 0;
    uint32_t* currentElem;
    uint32_t* dataArray = this->dataArray;       // +0x00
    int32_t count = this->count;                 // +0x04

    // Search for insertion point (sorted ascending)
    if (count > 0) {
        currentElem = dataArray;
        do {
            if (*valuePtr == *currentElem) {
                return nullptr;                  // duplicate found
            }
            if (*valuePtr < *currentElem) {
                break;                           // found first larger element
            }
            i++;
            currentElem++;
        } while (i < count);
    }

    // Allocate space for new node and store the value
    uint32_t* newNode = allocateInsertNode();
    *newNode = *valuePtr;

    // Return pointer past the stored key (presumably to a data field)
    return newNode + 1;
}