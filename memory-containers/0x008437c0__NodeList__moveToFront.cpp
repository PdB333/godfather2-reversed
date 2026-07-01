// FUNC_NAME: NodeList::moveToFront
void NodeList::moveToFront(Node* node)
{
    // node->pNext at offset 0x48, node->pPrev at offset 0x4c
    // Static list head returned by getListHead()
    ListHead* head = (ListHead*)FUN_00843740(); // returns pointer to static head

    if (node == 0) {
        // If null, call a virtual function from a global singleton (DAT_01205590)
        (**(code**)(*DAT_01205590 + 4))();
        return;
    }

    // If node is already the first element (head->pFirst points to node->pNext), do nothing
    if (head->pFirst == &node->pNext) {
        return;
    }

    // Remove the current first element from the list
    if (head->pFirst != 0) {
        FUN_004daf90(head); // remove first node
    }

    // Insert node at the front
    head->pFirst = &node->pNext; // head points to node's next pointer
    if (&node->pNext != 0) {
        head->pLast = node->pPrev; // update tail pointer
        node->pPrev = head; // node's prev now points to head
    }
}