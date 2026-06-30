// FUNC_NAME: FreeList::pop
void __thiscall FreeList::pop(void)
{
    Node* node = this->head; // +0x08

    if (node == nullptr)
    {
        this->populate(); // FUN_006e73f0 - initialize free list
        node = this->head;
    }

    this->head = node->next;  // remove head node
    node->next = nullptr;     // detach node
    this->count++;            // +0x0C - track number of nodes popped
}