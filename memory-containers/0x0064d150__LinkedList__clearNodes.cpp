// FUNC_NAME: LinkedList::clearNodes
void __fastcall LinkedList::clearNodes(LinkedList* thisv)
{
    // Set vtable pointer (offset +0x00) to a global vtable address
    thisv->vtable = &g_LinkedListVtable;  // PTR_LAB_00e42de4, identified as vtable for LinkedList class

    // Traverse the linked list starting from head (offset +0x04)
    LinkedListNode* currentNode = thisv->head;  // param_1[1] = head
    while (currentNode != nullptr) {
        LinkedListNode* nextNode = currentNode->next;  // offset +0x08 within node: next pointer
        // Clear node data fields (offset +0x00 and +0x04) and next pointer (offset +0x08)
        currentNode->data1 = 0;  // param_2[0] = first int/ptr
        currentNode->data2 = 0;  // param_2[1] = second int/ptr
        currentNode->next = 0;   // param_2[2] = next pointer
        currentNode = nextNode;
    }
    // Note: head pointer is not updated; this is likely called before node memory deallocation.
}