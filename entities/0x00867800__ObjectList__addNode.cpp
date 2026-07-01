// FUNC_NAME: ObjectList::addNode
void __thiscall ObjectList::addNode(int *this) {
    // this is a struct with:
    // +0x00: head (Node*)
    // +0x04: tail (Node*)
    // +0x08: count (int)
    // +0x0C: allocator (Allocator*)
    // +0x10: allocatorInterface (AllocatorInterface*) - used to call allocate()
    Allocator *allocator = (Allocator *)this[3]; // +0x0C
    if (allocator == nullptr) {
        allocator = (Allocator *)&DAT_01218a14; // global default allocator
    }
    // Allocate 0x24 (36) bytes using the allocator interface at this[4]
    Node *newNode = (Node *)this[4]->allocate(0x24, allocator);
    if (newNode != nullptr) {
        // Construct/didate the node; unaff_ESI is likely the 'this' of the list (or another context)
        // Passed implicitly in register ESI from the caller
        FUN_00867510((int)this); // assume ESI holds 'this'
    }
    // Insert at head of doubly linked list
    newNode->prev = (Node *)this[0]; // +0x1C: prev pointer
    if (this[0] != 0) {
        ((Node *)this[0])->next = newNode; // +0x20: next pointer
    }
    this[2] = this[2] + 1; // +0x08: count++
    this[0] = (int)newNode; // +0x00: head = newNode
    if (this[1] == 0) {
        this[1] = (int)newNode; // +0x04: tail = newNode (if list was empty)
    }
}