// FUNC_NAME: GameObject::destroy
void __thiscall GameObject::destroy(GameObject *this) {
    int headNode;
    int *nodePtr;
    int *predecessor;

    // Set vtable pointers for multiple inheritance
    this->vfptr[0] = &PTR_FUN_00e331e8;          // +0x00 main vtable
    this->vfptr[0xF] = &PTR_LAB_00e33204;        // +0x3C second base
    this->vfptr[0x12] = &PTR_LAB_00e33214;       // +0x48 third base
    this->vfptr[0x14] = &PTR_LAB_00e33218;       // +0x50 fourth base

    // If the flag at +0xE0 is non-zero and bit 1 at +0xE4 is clear, run additional cleanup
    if ((this->m_flags0 != 0) && ((this->m_flags1 >> 1 & 1) == 0)) {
        FUN_0047d330(); // likely deinit some subsystems
    }

    // Destroy three embedded sub-objects at offsets +0x54, +0x5C, +0x64
    FUN_004086d0(&this->m_subObj1);  // +0x15 (0x54)
    FUN_004086d0(&this->m_subObj2);  // +0x17 (0x5C)
    FUN_004086d0(&this->m_subObj3);  // +0x19 (0x64)
    FUN_00408310(&this->m_subObj1);  // deallocate sub-object 1
    FUN_00408310(&this->m_subObj2);  // deallocate sub-object 2
    FUN_00408310(&this->m_subObj3);  // deallocate sub-object 3

    // Clean up two global singletons
    FUN_004086d0(&DAT_012069c4);
    FUN_004086d0(&DAT_0120e93c);

    // Remove this object from a global linked list anchored at +0xD4
    headNode = this->m_listHead;        // +0x35 (0xD4) – pointer to first real node
    if (headNode != 0) {
        nodePtr = *(int **)(headNode + 4);  // next pointer of the first node
        if (nodePtr == &this->m_listHead) { // list has only this node (next points back to dummy)
            *(int *)(headNode + 4) = this->m_listTail; // +0x36 (0xD8) – tail pointer
            this->vfptr[0x14] = &PTR_LAB_00e32854; // set final vtable for deletion
            FUN_0046c640(); // likely operator delete or finalize
            return;
        }
        // Walk the list to find predecessor of the removed node
        predecessor = (int *)nodePtr[1];
        while (predecessor != &this->m_listHead) {
            nodePtr = (int *)nodePtr[1];
            predecessor = (int *)nodePtr[1];
        }
        nodePtr[1] = this->m_listTail; // update predecessor's next to tail
    }

    this->vfptr[0x14] = &PTR_LAB_00e32854; // set final vtable for deletion
    FUN_0046c640(); // likely operator delete or finalize
}