// FUNC_NAME: NodeOwner::operator=
int __thiscall NodeOwner::operator=(NodeOwner *this, NodeOwner *other)
{
    // Copy int at offset 4 (e.g., m_refCount or some ID)
    *(int *)(this + 4) = *(int *)(other + 4);

    // Copy linked list head pointer (m_head) with proper ownership transfer
    int **thisHead = (int **)(this + 8);
    int **otherHead = (int **)(other + 8);
    if (thisHead != otherHead) {
        int *newNode = *otherHead;
        if (*thisHead != newNode) {
            // Release old node if it exists
            if (*thisHead != 0) {
                FUN_004daf90(thisHead); // likely Node::release or delete
            }
            *thisHead = newNode;
            if (newNode != 0) {
                // Update prev pointer of new node to point back to this->m_head
                *(int **)(this + 0xc) = *(int **)(newNode + 4); // store old prev (might be next?)
                *(int **)(newNode + 4) = thisHead;
            }
        }
    }

    // Copy 8-byte value at offset 0x10 (e.g., a 64-bit timestamp or two ints)
    *(long long *)(this + 0x10) = *(long long *)(other + 0x10);
    // Copy int at offset 0x18
    *(int *)(this + 0x18) = *(int *)(other + 0x18);
    // Copy byte at offset 0x1c
    *(char *)(this + 0x1c) = *(char *)(other + 0x1c);
    // Copy int at offset 0x20
    *(int *)(this + 0x20) = *(int *)(other + 0x20);

    return (int)this;
}