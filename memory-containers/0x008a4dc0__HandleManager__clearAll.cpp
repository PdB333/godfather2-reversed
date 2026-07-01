// FUNC_NAME: HandleManager::clearAll
// Address: 0x008a4dc0
// Role: Clears all managed nodes and resets the slot array
// This function frees all nodes in the linked list and zeroes the slot pointer array.
// The class manages a fixed-capacity array of slots (each slot holds a pointer to a node).
// Nodes are intrusive linked list with self-pointer at offset 0 and next pointer at offset 8.

struct Node {
    Node* self;       // +0x00: pointer to itself (for validation)
    void* data;       // +0x04: user data (not used in clear)
    Node* next;       // +0x08: pointer to next node
};

// External freeing functions (likely from the memory pool)
extern void detachNode(Node* pNode);
extern void freeNode(Node* pNode);

class HandleManager {
public:
    // Cleanup: delete all nodes and reset slots
    void clearAll();

private:
    int**  m_ppSlots;          // +0x00: pointer to array of slot pointers (each slot is Node**)
    int    m_activeCount;      // +0x04: number of active nodes
    int    m_capacity;         // +0x08: size of slot array
    int    m_unknown;          // +0x0C: unused in this function
    int    m_totalAllocated;   // +0x10: total nodes allocated (decremented during free)
};

void HandleManager::clearAll() {
    // Get the first slot pointer from the slot array
    Node** slotArray = *m_ppSlots; // dereference to get actual array base (when m_ppSlots is pointer to pointer)
    Node* currentNode = *slotArray; // first slot's value (pointer to first node)

    while (currentNode != nullptr) {
        // Get the next node's self pointer by following the next field
        Node* nextNodeSelf = *(currentNode->next); // next is pointer to Node, so *next gives the self pointer of that node
        // Release the next node (pass its address)
        detachNode(currentNode->next);
        // Free the current node
        freeNode(currentNode);

        // Decrement total allocated count
        m_totalAllocated--;

        // Move to next node
        currentNode = nextNodeSelf;
    }

    // Zero out all slot pointers in the array
    for (int i = 0; i <= m_capacity; i++) {
        (*m_ppSlots)[i] = nullptr; // set each slot to null
    }

    // Reset active count
    m_activeCount = 0;
}