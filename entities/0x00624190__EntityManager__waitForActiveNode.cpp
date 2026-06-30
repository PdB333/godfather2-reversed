// FUNC_NAME: EntityManager::waitForActiveNode
struct Node {
    int field_0x0;
    Node* next;          // +0x8
    char activeFlag;     // +0x15
};

void EntityManager::waitForActiveNode() {
    Node* node = *(Node**)(this + 8);  // get head of linked list at this+0x8
    while (node->activeFlag == '\0') {
        node = node->next;             // traverse to next node at node+0x8
    }
}