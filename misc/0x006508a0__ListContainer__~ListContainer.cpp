// FUNC_NAME: ListContainer::~ListContainer
// Destructor for a class that contains a singly linked list of nodes with two vtable pointers.
// Clears all nodes in the linked list, then optionally deletes the container itself.
// Address: 0x006508a0

undefined4* __thiscall ListContainer::~ListContainer(undefined4* this, byte flag)
{
    undefined4* currentNode;
    undefined4* nextNode;

    // Set vtable pointers: offset 0x00 and offset 0x18
    this[6] = &PTR_LAB_00e317cc;   // +0x18: base class vtable?
    *this = &PTR_LAB_00e42de4;     // +0x00: derived vtable

    // Walk the linked list starting at offset 0x04 (head pointer)
    currentNode = (undefined4*)this[1];  // +0x04: head of list
    while (currentNode != (undefined4*)0x0) {
        nextNode = (undefined4*)currentNode[2]; // +0x08: next node pointer
        // Zero out node fields (offsets 0, 4, 8)
        *currentNode = 0;       // +0x00
        currentNode[1] = 0;     // +0x04
        currentNode[2] = 0;     // +0x08
        currentNode = nextNode;
    }

    // If flag & 1, deallocate this object
    if ((flag & 1) != 0) {
        heapDelete(this);   // calls operator delete or similar
    }

    return this;
}