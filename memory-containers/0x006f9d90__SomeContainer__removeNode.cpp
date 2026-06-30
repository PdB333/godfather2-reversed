// FUNC_NAME: SomeContainer::removeNode
void __thiscall SomeContainer::removeNode(int this, void* node)
{
    void* listNode;
    void* savedNext;
    unsigned int index;
    void** arrayIter;

    // Obtain the list node from the element at offset 0x48
    if (node == 0) {
        listNode = 0;
    } else {
        listNode = (void*)((int)node + 0x48);
    }

    // Unlink the node from its list: save next pointer and set next to point to its own address on stack
    savedNext = 0;
    if (listNode != 0) {
        savedNext = *(void**)((int)listNode + 4);  // +0x04: next pointer
        *(void**)((int)listNode + 4) = &listNode;  // set next to point to itself (stack variable)
    }

    // Search for the node in the internal array of pointers (size at +0x24, pointer array at +0x20)
    index = 0;
    if (*(unsigned int*)(this + 0x24) != 0) {
        arrayIter = *(void***)(this + 0x20); // array of pointers, each entry 8 bytes (increment by 2 pointers)
        do {
            if (*arrayIter == listNode) {
                // Found: jump to cleanup (skip the remove call) unless index overflow
                if (index != 0xFFFFFFFF) {
                    goto cleanup;
                }
                break;
            }
            index++;
            arrayIter += 2; // step by 2 pointers (8 bytes per entry)
        } while (index < *(unsigned int*)(this + 0x24));
    }

    // If not found, call remove operation on the list node
    FUN_006bd130(&listNode);

cleanup:
    // Free the list node if still valid
    if (listNode != 0) {
        FUN_004daf90(&listNode);
    }
    return;
}