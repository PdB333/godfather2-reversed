// FUNC_NAME: MemoryPoolNode::MemoryPoolNode
void __thiscall MemoryPoolNode::MemoryPoolNode(MemoryPoolNode *this, void *pBase, uint unk1, uint unk2, uint unk3, uint alignment)
{
    this->pNext = g_pBlockListHead; // +0x04: previous head of the linked list
    this->field_08 = unk2;          // +0x08
    this->field_18 = unk1;          // +0x18
    this->field_24 = unk3;          // +0x24
    this->field_0C = 0;             // +0x0C: cleared
    this->field_10 = 0;             // +0x10: cleared
    this->field_14 = 0;             // +0x14: cleared
    this->field_1C = 0;             // +0x1C: cleared
    this->field_30 = 0;             // +0x30: cleared
    this->field_34 = 0;             // +0x34: cleared
    this->field_20 = alignment;     // +0x20: stored alignment/size
    this->field_2C = pBase;         // +0x2C: base pointer passed
    this->field_28 = (void *)((uint)((char*)pBase - 1 + alignment) & ~(alignment - 1U)); // aligned address
    this->vtable = &g_vtableMemoryPoolNode; // +0x00: vtable pointer from global
    g_pBlockListHead = this;                 // update head to new node
}