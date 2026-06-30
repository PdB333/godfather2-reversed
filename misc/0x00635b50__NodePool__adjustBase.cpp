// FUNC_NAME: NodePool::adjustBase
// Function address: 0x00635b50
// Recalculates internal offsets (aligned to 8 bytes) after a memory block relocation.
// This is used to update pointers stored as relative offsets from a base pointer.
// The pool contains fixed-size nodes (8 bytes each) and an array of pairs (24-byte stride).

void __thiscall NodePool::adjustBase(int oldBase)
{
    // +0x08: head pointer (relative offset from pool base)
    // +0x1c: new base pointer after relocation
    this->head = this->base + ((this->head - oldBase) >> 3) * 8;

    // +0x48: free list linked list head (each node stores next pointer at offset 0)
    Node* node = this->freeList;
    while (node != nullptr)
    {
        // +0x08 from each node: a pointer field that also needs relocation
        node->fieldOffset = this->base + ((node->fieldOffset - oldBase) >> 3) * 8;
        node = node->next; // next pointer is at offset 0
    }

    // +0x28: start of array of pairs (each pair occupies 6 ints = 24 bytes)
    // +0x14: end pointer of the array
    int* entry = this->arrayStart;
    while (entry <= this->arrayEnd)
    {
        // entry[0] and entry[1] are relative offsets
        entry[1] = this->base + ((entry[1] - oldBase) >> 3) * 8;
        entry[0] = this->base + ((entry[0] - oldBase) >> 3) * 8;
        entry += 6; // stride to next pair
    }

    // +0x0c: set to the first element of the array (absolute pointer after relocation)
    this->firstArrayElement = *this->arrayStart;
}