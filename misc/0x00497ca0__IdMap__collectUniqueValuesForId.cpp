// FUNC_NAME: IdMap::collectUniqueValuesForId
// Address: 0x00497ca0
// Role: Collects unique values associated with a given ID from a linked list of nodes,
// each containing a dynamic array of (id, data) pairs. Sorts and deduplicates the results.

// Assumes __thiscall: this in ECX, searchId on stack, outputArray in ESI (unaff_ESI)
// OutputArray structure: [ int* buffer; int size; int capacity; ]

void IdMap::collectUniqueValuesForId(int searchId, DynamicArray* outputArray) {
    // Class fields:
    // +0x00: vtable or ref count?
    // +0x04: pointer to container (Container*)
    Container* container = *(Container**)((char*)this + 0x04);
    
    // Initialize output array (assumed caller-allocated on stack)
    outputArray->buffer = nullptr;
    outputArray->size = 0;
    outputArray->capacity = 0;
    
    // Get head of linked list from container
    // Container likely has: some fields, then List* at +0x10
    Node* currentNode = nullptr;
    if (container != nullptr) {
        currentNode = *(Node**)((char*)container + 0x10);
    }
    
    // Iterate through all nodes
    while (currentNode != nullptr) {
        // Node layout:
        // +0x00: int value
        // +0x04: Pair* pairs (array of (id, data))
        // +0x08: int pairCount
        // +0x0C: Node* next
        Pair* pairs = currentNode->pairs;
        int pairCount = currentNode->pairCount;
        
        if (pairs != nullptr && pairCount > 0) {
            // Iterate over pairs (each pair is 8 bytes: id + data)
            Pair* end = (Pair*)((unsigned char*)pairs + pairCount * 8);
            for (Pair* p = pairs; p < end; ++p) {
                if (p->id == searchId) {
                    // Grow array if needed
                    if (outputArray->size == outputArray->capacity) {
                        int newCapacity = (outputArray->capacity == 0) ? 1 : (outputArray->capacity * 2);
                        reallocateArray(outputArray, newCapacity);
                    }
                    outputArray->buffer[outputArray->size] = currentNode->value;
                    outputArray->size++;
                }
            }
        }
        currentNode = currentNode->next;
    }
    
    // Sort the collected values
    if (outputArray->size > 0) {
        sortIntArray(outputArray->buffer, outputArray->size);
    }
    
    // Remove duplicates (in-place, shrinking the array)
    int* buf = outputArray->buffer;
    int newSize = 0;
    if (outputArray->size > 0) {
        int* readPtr = buf;
        int* writePtr = buf;
        while (readPtr < buf + outputArray->size) {
            // Skip duplicates
            while (readPtr < buf + outputArray->size && *readPtr == *writePtr) {
                ++readPtr;
            }
            if (readPtr < buf + outputArray->size) {
                ++writePtr;
                *writePtr = *readPtr;
                ++readPtr;
            }
        }
        newSize = (writePtr - buf) + 1;
    }
    shrinkArray(outputArray, newSize);
}