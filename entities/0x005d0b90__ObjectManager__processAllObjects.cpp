// FUNC_NAME: ObjectManager::processAllObjects
// Function address: 0x005d0b90
// Role: Drains a singly-linked list by processing and removing each node.
// The list is stored in a structure with two fields:
//   m_pHead at offset +0x00
//   m_pCurrent at offset +0x04
// Each node has a next pointer at offset +0x20.
// The function calls a method on each node (FUN_005d12b0) and
// advances the head if the current node is also the head,
// effectively removing it from the list.

class ObjectManager {
    struct Node {
        // +0x00: unknown (likely other data)
        // +0x20: pointer to next node
        Node* m_pNext;
        void process(); // FUN_005d12b0 - processes this node
    };

    Node* m_pHead;    // +0x00
    Node* m_pCurrent; // +0x04

public:
    void processAllObjects();
};

void ObjectManager::processAllObjects() {
    Node* node;

    node = this->m_pHead;
    while (node != nullptr) {
        node = this->m_pCurrent;
        if (node != nullptr) {
            // Advance current to the next node
            this->m_pCurrent = node->m_pNext;
            // If the current node is the head, advance the head as well
            if (this->m_pHead == node) {
                this->m_pHead = this->m_pHead->m_pNext;
            }
            // Process the node
            node->process();
        }
        // If current became null (end of list), wrap around to head
        if (this->m_pCurrent == nullptr) {
            this->m_pCurrent = this->m_pHead;
        }
        // Re-evaluate loop condition with the possibly updated head
        node = this->m_pHead;
    }
}