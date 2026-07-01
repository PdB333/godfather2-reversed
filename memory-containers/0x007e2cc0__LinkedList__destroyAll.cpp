// FUNC_NAME: LinkedList::destroyAll
void __thiscall LinkedList::destroyAll(LinkedList* this)
{
    Node* node = this->head;  // +0x00
    while (node != 0) {
        Node* nextNode = node->next;  // +0x0C (node[3])
        this->current = nextNode;      // +0x04 (this[1])
        if (node->pManagedObject != 0) {  // +0x00 (node[0])
            releaseManagedObject(node->pManagedObject);  // FUN_004daf90
        }
        // Call virtual destructor or release via allocator vtable (offset +0x10)
        // this->allocator is a pointer to an object with vtable; second method is NodeRelease
        this->allocator->releaseNode(node, 0);  // this[4] -> vtable[1] (offset +4)
        node = nextNode;
        this->head = node;  // +0x00
    }
    this->current = 0;  // +0x04
    this->head = 0;     // +0x00
    this->count = 0;    // +0x08
}