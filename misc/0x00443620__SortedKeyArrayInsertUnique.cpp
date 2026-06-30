// FUNC_NAME: SortedKeyArrayInsertUnique

// Sorted array of 20-byte elements (5 uint32s). First 4 uint32s form a unique composite key.
// Elements are maintained in ascending lexicographic order of the key.
// The 5th uint32 is a data payload slot.
struct SortedKeyArray {
    uint32_t* elements; // +0x00: pointer to array of 5-uint32 elements
    int32_t count;      // +0x04: number of elements currently in array
};

extern uint32_t* allocateKeyNode(); // from FUN_00443bd0 – allocates 20 bytes, returns pointer

// Attempts to insert a key (4 uint32s). If key already exists, returns NULL.
// Otherwise allocates a new element, copies key, and returns pointer to the 5th uint32 data slot.
uint32_t* SortedKeyArrayInsertUnique(SortedKeyArray* array, uint32_t key[4])
{
    int32_t i = 0;
    if (array->count > 0) {
        uint32_t* element = array->elements;
        do {
            uint32_t elem0 = element[0];
            // Compare key[0..3] with element[0..3] respectively.
            // If equal, duplicate found -> return NULL.
            if (key[0] == elem0 && key[1] == element[1] && key[2] == element[2] && key[3] == element[3]) {
                return (uint32_t*)0x0;
            }
            // Stop if key is less than element (lexicographic).
            if (key[0] < elem0) break;
            if (key[0] == elem0) {
                if (key[1] < element[1]) break;
                if (key[1] == element[1]) {
                    if ((key[2] < element[2]) ||
                        (key[2] == element[2] && (key[3] < element[3]))) break;
                }
            }
            // Otherwise key is greater, move to next element.
            i++;
            element += 5; // each element is 5 uint32s
        } while (i < array->count);
    }
    // Key not found; allocate new element and copy key.
    uint32_t* newNode = allocateKeyNode();
    newNode[0] = key[0];
    newNode[1] = key[1];
    newNode[2] = key[2];
    newNode[3] = key[3];
    // Return pointer to the 5th uint32 (data slot) of the new node.
    return newNode + 4;
}