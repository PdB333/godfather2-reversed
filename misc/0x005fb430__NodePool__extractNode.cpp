// FUNC_NAME: NodePool::extractNode
struct Node {
    Node* next; // +0x00
    Node* prev; // +0x04
    // data at +0x08 (size 0xC total)
};

struct Container {
    Node* head; // +0x18 (based on assertion)
    // other fields...
};

struct NodeInfo {
    Container* container;
    Node* next; // the node that followed the removed one
};

void NodePool::extractNode(Container* container, Node* node, NodeInfo* outInfo) {
    // Validate inputs
    if (container == nullptr) {
        debugAssertFail();
    }
    if (node == container->head) {
        debugAssertFail(); // cannot remove sentinel head
    }

    Node* nextNode = node->next; // capture before node is freed

    // Unlink node from doubly linked list
    if (node != this->tail) { // tail is a sentinel, never freed
        node->prev->next = nextNode;
        nextNode->prev = node->prev;

        // Free the node (0xC bytes) via virtual function at vtable+4
        (this->vtable[1])(node, 0xC); // deallocate
        this->count--;
    }

    // Prepare output
    outInfo->container = container;
    outInfo->next = nextNode;
}