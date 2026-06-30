// FUNC_NAME: LinkedList::constructor
undefined4 * __thiscall LinkedList::constructor(LinkedList *this, byte allocFlag)
{
    undefined4 *currentNode;
    undefined4 *nextNode;
    
    // Set vtable pointers (multiple inheritance)
    this->vtable2 = &PTR_LAB_00e317cc;   // +0x18 (offset 24)
    this->vtable1 = &PTR_LAB_00e42de4;   // +0x00
    
    // Traverse the linked list starting at head (+0x04) and clear each node
    currentNode = (undefined4 *)this->head;  // +0x04
    while (currentNode != (undefined4 *)0x0) {
        nextNode = (undefined4 *)currentNode[2];  // Node next pointer at offset 8
        currentNode[0] = 0;   // Clear field at offset 0
        currentNode[1] = 0;   // Clear field at offset 4
        currentNode[2] = 0;   // Clear next pointer at offset 8
        currentNode = nextNode;
    }
    
    // If the object was heap-allocated, schedule deallocation
    if ((allocFlag & 1) != 0) {
        freeMemory(this);  // FUN_009c8eb0
    }
    return this;
}