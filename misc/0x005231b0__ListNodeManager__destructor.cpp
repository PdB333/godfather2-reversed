// FUNC_NAME: ListNodeManager::destructor

void __fastcall ListNodeManager::destructor(ListNodeManager *this)
{
    ListNode *currentNode;
    ListNode *prevNode;
    ListNode *nextNode;
    ListNode **slotPtr;
    ListNode **headPtr;
    int slotIndex;

    // Set vtable pointer
    this->vtable = &g_vtable_00e38350;

    // Remove the head of the free list
    headPtr = &this->freeListHead; // offset +0x116
    currentNode = this->freeListHead; // offset +0x116
    if (currentNode != nullptr)
    {
        nextNode = currentNode->next; // offset +0x04 in ListNode
        if (nextNode == reinterpret_cast<ListNode *>(headPtr))
        {
            headPtr->next = reinterpret_cast<ListNode *>(this->freeListNext); // offset +0x117
        }
        else
        {
            prevNode = nextNode->next; // actually nextNode is a pointer, nextNode->next is at nextNode+4
            while (prevNode != reinterpret_cast<ListNode *>(headPtr))
            {
                nextNode = prevNode;
                prevNode = nextNode->next;
            }
            nextNode->next = reinterpret_cast<ListNode *>(this->freeListNext);
        }
    }

    // Iterate through 6 slots (each 0x28 bytes apart) and remove their contents
    slotPtr = reinterpret_cast<ListNode **>(reinterpret_cast<char *>(this) + 0x114); // start at last slot
    slotIndex = 5;
    do
    {
        // Each slot has a pointer at the beginning
        currentNode = slotPtr[0]; // offset -0x28 from previous slot? Actually slotPtr points to base of each slot
        if (currentNode != nullptr)
        {
            ListNode *node = reinterpret_cast<ListNode *>(reinterpret_cast<char *>(currentNode) + 4); // node->next pointer
            if (node == reinterpret_cast<ListNode *>(slotPtr))
            {
                // The node's next pointer points back to the slot itself (sentinel)
                currentNode->next = reinterpret_cast<ListNode *>(slotPtr[1]); // slotPtr[1] is at slotPtr+4 which is the next field in the slot? Actually slotPtr[1] is not defined; careful.
                // The original code uses puVar7[-0x27], which is at puVar8+4. So slotPtr+4 contains a pointer to the next node.
            }
            else
            {
                ListNode *prev = node->next;
                while (prev != reinterpret_cast<ListNode *>(slotPtr))
                {
                    node = prev;
                    prev = node->next;
                }
                node->next = reinterpret_cast<ListNode *>(slotPtr[1]); // slotPtr[1] is the next field in the slot
            }
        }
        slotIndex--;
        slotPtr = reinterpret_cast<ListNode **>(reinterpret_cast<char *>(slotPtr) - 0x28); // move to previous slot
    } while (slotIndex >= 0);

    // Set final vtable pointer (probably destructor complete)
    this->vtable = &g_vtable_00e38340;
}