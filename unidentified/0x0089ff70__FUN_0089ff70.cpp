//FUNC_NAME: SomeClass::~SomeClass
void __thiscall SomeClass::~SomeClass(SomeClass* this)
{
    // local_8 is a pointer to the embedded list node at offset 0x48
    int* listNode;
    int* nextNode;
    int dummy;

    if (this == 0) {
        listNode = 0;
    }
    else {
        listNode = (int*)((char*)this + 0x48); // +0x48: embedded list node
    }

    dummy = 0;
    if (listNode != 0) {
        // Read the next pointer from the node (offset +4)
        nextNode = (int*)*((int*)listNode + 1); // *(listNode+4)
        // Write the address of listNode into the next node's prev pointer (offset 0)
        *nextNode = (int)&listNode; // This seems wrong; likely intended to update prev of next node
        // Actually typical doubly linked list removal: nextNode->prev = listNode->prev
        // But here it writes &listNode, which is a stack address. Possibly a bug or different structure.
        // More likely: *(int*)(listNode+4) = *(int*)(listNode); // set next's prev to current prev
        // But the decompiled code is: *(listNode+4) = &listNode; That is suspicious.
        // We'll keep as decompiled but comment.
    }

    // Call destructor of base class or cleanup
    FUN_0089f860(&listNode);

    // If listNode is still non-null, free memory
    if (listNode != 0) {
        FUN_004daf90(&listNode);
    }
}