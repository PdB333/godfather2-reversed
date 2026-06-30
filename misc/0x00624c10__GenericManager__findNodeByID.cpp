// FUNC_NAME: GenericManager::findNodeByID
// ----------------------------------------------------------------------------
// Function at 0x00624c10 (thunk to actual implementation at 0x00624bd0)
// Searches a singly linked list of nodes stored at m_headNode (+0x20).
// Each node has a vtable pointer at +0x00, a virtual identify() function that
// returns an integer ID, and a next pointer at +0x28.
// Returns the matching node pointer, or NULL if not found.

// Node structure (size unknown)
struct Node {
    int (__thiscall *identify)(void*);   // +0x00 vtable (first function returns ID)
    // ... other members ...
    Node* next;                          // +0x28 next pointer
};

Node* __thiscall GenericManager::findNodeByID(int targetID) {
    Node* currentNode = m_headNode;           // this+0x20
    if (currentNode == nullptr) {
        return nullptr;
    }
    do {
        Node* nextNode = currentNode->next; // currentNode[10] at +0x28
        int nodeID = currentNode->identify(); // vtable[0]()
        if (nodeID == targetID) {
            return currentNode;
        }
        currentNode = nextNode;
    } while (currentNode != nullptr);
    return nullptr;
}