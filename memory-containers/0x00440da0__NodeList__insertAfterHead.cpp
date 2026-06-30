// FUNC_NAME: NodeList::insertAfterHead

struct Node {
    Node *prev;  // +0x00
    Node *next;  // +0x04
};

// Forward declarations of called functions
Node* __fastcall allocateNodeFromPool(Node *pool, Node *next, void *unused);
void __fastcall lockMutex(void);

void __thiscall NodeList::insertAfterHead(NodeList *this) {
    Node *head = *(Node **)((char *)this + 0x18);       // get list head (sentinel node)
    Node *newNode = allocateNodeFromPool(head, head->next, EDX); // allocate a node, passing head and its next pointer
    lockMutex();                                          // acquire lock for list manipulation

    head->next = newNode;               // link head to new node
    newNode->next->prev = newNode;      // link the node that was originally after head back to new node
}