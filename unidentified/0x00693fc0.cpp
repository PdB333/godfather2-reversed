// FUN_NAME: findFirstActiveNode
// Function at 0x00693fc0: Traverses a linked list from a container's head (+0x8) until a node with a non-zero char at +0x25 is found.
// Assumes the list is non-null and that such a node always exists (no null check in loop).
// The found node is not returned or used – this may be a validation or side-effect placeholder.

struct Node {
    char pad_0x00[0x08];
    Node* next; // +0x8
    // ... other fields ...
    char flag;   // +0x25
};

struct Container {
    char pad_0x00[0x08];
    Node* head;  // +0x8
};

void __thiscall Container::findFirstActiveNode() {
    Node* node = this->head;
    char flag = node->flag;               // +0x25
    while (flag == '\0') {
        node = node->next;                // +0x8
        flag = node->flag;                // +0x25
    }
    // Loop exits when a node with non-zero flag is found; no further action.
}