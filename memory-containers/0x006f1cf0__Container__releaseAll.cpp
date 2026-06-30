// FUNC_NAME: Container::releaseAll
// Address: 0x006f1cf0
// Role: Iterates a linked list of allocated nodes, releases each via allocator, then releases an extra node, and finally shuts down the allocator.
// The container structure:
//   +0x00: head (Node*) - start of linked list
//   +0x04: unused (int)
//   +0x08: unused (int)
//   +0x0C: extraNode (Node*) - a standalone node to release
//   +0x10: alloc (Allocator*) - pointer to an allocator with virtual methods at vtable+4 (release) and vtable+12 (shutdown)
// Node structure:
//   +0x00: data (int)
//   +0x04: next (Node*)

struct Node {
    int field_0;
    Node* next;
};

struct Allocator {
    virtual void release(Node* node, int flag);
    virtual void unknown2();
    virtual void unknown3();
    virtual void shutdown();
};

struct Container {
    Node* head;        // +0x00
    int unused1;       // +0x04
    int unused2;       // +0x08
    Node* extraNode;   // +0x0C
    Allocator* alloc;  // +0x10
};

void __fastcall Container::releaseAll(Container* this)
{
    Node* currentNode = this->head;
    while (currentNode != nullptr) {
        Node* nextNode = currentNode->next;
        this->alloc->release(currentNode, 0);
        currentNode = nextNode;
    }
    if (this->extraNode != nullptr) {
        this->alloc->release(this->extraNode, 0);
    }
    this->alloc->shutdown();
}