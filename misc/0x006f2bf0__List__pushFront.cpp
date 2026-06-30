// FUNC_NAME: List::pushFront
// Function at 0x006f2bf0: Inserts a new node at the front of a doubly linked list.
// Uses an allocator object (likely virtual) stored in the list descriptor.
// The value to insert is passed in ESI (not captured in the decompiled signature).
// List structure:
//   +0x00: Node* head
//   +0x04: Node* tail
//   +0x08: int count
//   +0x0C: void* pool (context for allocation)
//   +0x10: Allocator* allocator (with virtual allocate method)
// Node structure:
//   +0x00: uint32_t data
//   +0x04: Node* next
//   +0x08: Node* prev

// Forward declaration of allocator interface
struct NodeAllocator
{
    virtual void* allocate(uint32_t size, void* context) = 0; // first vtable entry
};

struct Node
{
    uint32_t data;   // +0x00
    Node*    next;   // +0x04
    Node*    prev;   // +0x08
};

struct List
{
    Node*        head;       // +0x00
    Node*        tail;       // +0x04
    int          count;      // +0x08
    void*        pool;       // +0x0C (context passed to allocator)
    NodeAllocator* allocator; // +0x10
};

void __fastcall List::pushFront(List* thisList) // ECX = thisList, value in ESI
{
    Node* newNode;
    Node* poolContext;

    // Obtain pool context; if null, use a global default
    poolContext = (Node*)thisList->pool;
    if (poolContext == nullptr)
    {
        poolContext = (Node*)DAT_01218a14; // global default pool
    }

    // Allocate a new Node via the allocator's virtual function
    // Passing size 12 bytes and the context
    newNode = (Node*)thisList->allocator->allocate(0xC, poolContext);
    if (newNode != nullptr)
    {
        // Initialize node: data from ESI, next=0, prev=0
        newNode->data = *unaff_ESI;
        newNode->prev = 0; // +0x08 set to 0 initially
        newNode->next = 0; // +0x04 set to 0 initially
    }

    // Link the new node at the front
    newNode->next = thisList->head; // new node's next points to current head
    if (thisList->head != nullptr)
    {
        thisList->head->prev = newNode; // old head's prev points to new node
    }
    thisList->count++; // increment size
    thisList->head = newNode; // head is now the new node

    // If the list was empty, also update tail
    if (thisList->tail == nullptr)
    {
        thisList->tail = newNode;
    }
}