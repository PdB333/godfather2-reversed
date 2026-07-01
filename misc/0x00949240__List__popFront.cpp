// FUNC_NAME: List::popFront
undefined4* __fastcall List::popFront(List* this)
{
    undefined4* node;
    undefined4 nextPtr;

    // Check if list is empty or in invalid state
    if ((this->head == 0) &&
        ((this->tail == 0) || ((this->flags & 1) == 0)))
    {
        assertEmptyList();
    }

    node = this->head;
    if (node != 0)
    {
        nextPtr = *node; // next pointer stored at offset 0 of node
        this->popCount++;   // +0x10
        this->size--;       // +0x0c
        this->head = nextPtr;
        return node;
    }
    return 0;
}