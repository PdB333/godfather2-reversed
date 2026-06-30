// FUNC_NAME: Node::getNextActive
// Function address: 0x005e1440
// Role: Starting from 'this' node, traverses a singly linked list (next pointer at +0x8) and returns the first node
//       where the byte flag at +0x15 is non-zero. The current node is skipped; search begins from this->next.
//       Used to find the next 'active' node in a chain (e.g., active entities, loaded objects).
// Offsets:
//   +0x08: pointer to next node in linked list (Node*)
//   +0x15: byte active flag (0 = inactive, non-zero = active)
// Calling convention: __thiscall (this pointer in ECX)

class Node {
public:
    Node* next;          // +0x08
    char activeFlag;     // +0x15 (byte)
};

// __thiscall
Node* Node::getNextActive() {
    Node* currentNode = this->next;
    while (currentNode->activeFlag == '\0') {
        currentNode = currentNode->next;
    }
    return currentNode;
}