// FUNC_NAME: LinkedList::remove
void __thiscall LinkedList::remove(LinkedList* this, int unused, LinkedListNode** nodePtr)
{
    LinkedListNode* node = *nodePtr;
    LinkedListNode* nextNode;

    if (node == nullptr)
    {
        nextNode = nullptr;
    }
    else
    {
        nextNode = node->next; // +0x04
    }

    *nodePtr = nextNode;

    if (node == this->head) // +0x00
    {
        if (node == this->tail) // +0x04 (only one node)
        {
            this->head = nullptr;
            this->tail = nullptr;
        }
        else
        {
            this->head = nextNode;
            if (nextNode != nullptr)
            {
                nextNode->prev = nullptr; // +0x08
            }
        }
    }
    else
    {
        LinkedListNode* prevNode = node->prev; // +0x08
        if (node == this->tail) // +0x04
        {
            this->tail = prevNode;
            prevNode->next = nullptr; // +0x04
        }
        else
        {
            prevNode->next = nextNode; // +0x04
            nextNode->prev = prevNode; // +0x08
        }
    }

    // Destroy the node via vtable at this+0x10 (+0x10), function at offset 4
    void (__thiscall* destroy)(LinkedListNode*, int) = 
        (void (__thiscall*)(LinkedListNode*, int))(*((int*)this->vtable + 1)); // offset 4
    destroy(node, 0);

    this->count--; // +0x08

    // Unused: *EBX = *nodePtr; (register output)
}