// FUNC_NAME: SortedArray::insertSorted
// Address: 0x008c4d30
// Inserts an element into a sorted dynamic array of (int id, float priority) pairs.
// The array is stored as a contiguous block of 12-byte entries (id, priority, reserved).
// param_1 = id, param_2 = pointer to SortedArray struct { Node* data; int count; int capacity; }

struct SortedArrayNode {
    int id;       // +0x00
    float priority; // +0x04
    int reserved;   // +0x08 (always set to 0)
};

struct SortedArray {
    SortedArrayNode* data;  // +0x00
    int count;              // +0x04
    int capacity;           // +0x08
};

// Forward declarations of helper functions from the binary (can't inline)
float computePriority(int id);                // 0x008bf060
SortedArrayNode* insertAtPosition(int index); // 0x008c23b0 - shifts elements and returns pointer to slot
void reallocateArray(int newCapacity);        // 0x008be170

float10 SortedArray_insert(int id, SortedArray* array) {
    float priority = computePriority(id);  // Get priority from external source
    float key = priority;                  // Used for comparison

    int i = 0;
    if (array->count != 0) {
        float* currentKey = &array->data[0].priority;
        do {
            if (priority < *currentKey) {
                // Found insertion point: insert at index i
                SortedArrayNode* slot = insertAtPosition(i);
                slot->id = id;
                slot->priority = priority;
                slot->reserved = 0;
                return (float10)priority;
            }
            i++;
            currentKey += 3; // Move by 3 floats (12 bytes) to next node's priority
        } while (i < array->count);
    }

    // If we reach here, the new element belongs at the end (or array is empty)
    if (i == array->count) {
        // Check if capacity is sufficient
        if (array->count == array->capacity) {
            int newCapacity = (array->capacity == 0) ? 1 : array->capacity * 2;
            reallocateArray(newCapacity);
        }
        // Write at the end
        SortedArrayNode* slot = &array->data[array->count];
        slot->id = id;
        slot->priority = priority;
        slot->reserved = 0;
        array->count++;
    }

    return (float10)priority;
}