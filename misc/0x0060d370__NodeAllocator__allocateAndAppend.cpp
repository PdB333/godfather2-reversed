// FUNC_NAME: NodeAllocator::allocateAndAppend

struct Node {
    int value;      // +0x00
    Node* next;     // +0x04
    Node* prev;     // +0x08
};

// Global allocator object (vtable with allocate)
static Allocator* gAllocator = (Allocator*)0x012224f0; // pointer to allocator with virtual allocate

// Source pointer for the value to copy
static int* gSourceData = (int*)0x012224ec; // if null, use default source
static int* gDefaultSource = (int*)0x01218a14; // default fallback source

// Linked list management
static Node* gHead = (Node*)0x012224e0; // head pointer
static Node* gTail = (Node*)0x012224e4; // tail pointer
static int gCount = *(int*)0x012224e8; // node count

void allocateAndAppend(void)
{
    int* src = gSourceData;
    if (src == 0) {
        src = gDefaultSource;
    }

    // Virtual call: allocator->allocate(12) – size of Node
    Node* newNode = (Node*)gAllocator->allocate(12);
    if (newNode != 0) {
        newNode->value = *src; // copy source value
        newNode->next = 0;
        newNode->prev = 0;
    }

    if (gTail != 0) {
        // Append new node after current tail
        gTail->next = newNode;      // old tail -> next = new
        newNode->prev = gTail;      // new -> prev = old tail
        gCount++;
        gTail = gTail->next;        // tail becomes new node
        return;
    }

    // Empty list: new node becomes both head and tail
    gCount++;
    gHead = newNode;
    gTail = newNode;
}