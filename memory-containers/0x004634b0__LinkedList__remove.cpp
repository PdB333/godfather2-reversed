// FUNC_NAME: LinkedList::remove
int* __thiscall LinkedList::remove(int* iterator)
{
    // iterator is a pointer to the current node pointer (like an iterator).
    // Node layout: +0x00 = next, +0x04 = prev, +0x08 = data (or more fields)
    // List header layout:
    //   +0x00 (head)
    //   +0x04 (tail)
    //   +0x08 (size)
    //   +0x10 (destructor vtable pointer - first entry is offset 4 method)
    
    int* list = (int*)this;  // ESI
    int** nodePtr = (int**)iterator; // EDI points to current node pointer
    
    int* node = *nodePtr; // current node to remove
    if (node == nullptr) {
        return iterator;
    }
    
    int* next = *(int**)(node + 4); // node->next
    int* prev = *(int**)(node + 8); // node->prev
    
    // Update head/tail pointers in list
    if (node == list[0]) // node is head
    {
        if (node == list[1]) // also tail (only node)
        {
            list[1] = 0; // tail = null
            list[0] = 0; // head = null
        }
        else
        {
            list[0] = next; // head = next
            if (next != nullptr)
                *(int**)(next + 8) = 0; // next->prev = null
        }
    }
    else
    {
        if (node == list[1]) // node is tail
        {
            list[1] = prev; // tail = prev
            *(int**)(prev + 4) = 0; // prev->next = null
        }
        else
        {
            // internal node: link prev and next together
            *(int**)(prev + 4) = next; // prev->next = node->next
            *(int**)(next + 8) = prev; // next->prev = prev
        }
    }
    
    // Call destructor on the node via the list's vtable
    // The vtable is at list[4], and the destructor function is at vtable[1] (offset 4)
    void (*destructor)(void*, int) = *(void(**)(void*, int))(*(int*)list[4] + 4);
    destructor(node, 0);
    
    // Decrement size
    list[2] = list[2] - 1;
    
    // Update iterator to point to the next node (or null if removed last)
    *nodePtr = next;
    return (int*)nodePtr;
}