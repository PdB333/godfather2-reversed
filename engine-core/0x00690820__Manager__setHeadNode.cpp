// FUNC_NAME: Manager::setHeadNode

// Address: 0x00690820
// Role: Sets the head of an intrusive doubly linked list to point to the given node.
// The list's head pointer is at +0x24B4, tail at +0x24B8.
// The node structure has link fields at +0x48 (next) and +0x4C (prev).

class Manager {
public:
    // Offsets assumed:
    // this + 0x24B4 : int* m_head;  // pointer to the "next" member of the first node
    // this + 0x24B8 : int* m_tail;  // pointer to the "prev" member of the last node? (used as tail)

    void setHeadNode(void* node);
};

// Forward declaration of cleanup function called on old head pointer
extern void cleanupListHead(int* headPtr);  // Address: 0x004DAF90

void Manager::setHeadNode(void* node) {
    // Get the address of the node's "next" field (offset +0x48)
    int* newHeadPtr = (node != nullptr) ? (int*)((uint8_t*)node + 0x48) : nullptr;

    // Compare with current head pointer
    int** thisHeadPtr = (int**)((uint8_t*)this + 0x24B4);
    if (*thisHeadPtr != newHeadPtr) {
        // Old head exists – clean it up (likely removes all nodes from the list)
        if (*thisHeadPtr != nullptr) {
            cleanupListHead(*thisHeadPtr);
        }

        // Set the new head
        *thisHeadPtr = newHeadPtr;

        if (newHeadPtr != nullptr) {
            // Copy the node's "prev" field (offset +0x4C) into the manager's tail slot
            // This assumes the node's prev initially pointed to the previous tail.
            int** tailPtr = (int**)((uint8_t*)this + 0x24B8);
            *tailPtr = *(int**)((uint8_t*)node + 0x4C);

            // Update the node's "prev" to point back to the head pointer (for circular/tagged list)
            *(int**)((uint8_t*)node + 0x4C) = thisHeadPtr;
        }
    }
}