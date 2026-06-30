// FUNC_NAME: NodeList::findFirstActive

// Function at 0x00694010
// Walks a linked list starting from head (offset +0x08 of this object)
// until it finds a node whose flag at offset +0x29 is non-zero.
// The found node is not used – the function likely guarantees at least one active node exists.
// __thiscall member function

class Node {
public:
    Node* next;      // +0x08
    // unknown fields at +0x0C to +0x28
    char activeFlag; // +0x29
};

class NodeList {
private:
    // unknown field(s) at offsets 0x00-0x07 (e.g. vtable, size, etc.)
    Node* head; // +0x08

public:
    void findFirstActive();
};

void NodeList::findFirstActive() {
    Node* currentNode = head;
    char flag = currentNode->activeFlag;

    while (flag == '\0') {
        currentNode = currentNode->next;
        flag = currentNode->activeFlag;
    }
    // Guarantees 'currentNode' points to a node with non-zero flag.
}