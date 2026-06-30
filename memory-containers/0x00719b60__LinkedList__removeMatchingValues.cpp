// FUNC_NAME: LinkedList::removeMatchingValues
void __thiscall LinkedList::removeMatchingValues(int *keyPtr) {
    ListNode *current = *(ListNode **)this; // head of linked list
    while (current != (ListNode *)0x0) {
        if (*keyPtr == current->data) {
            // Remove the node and get the next node after removal
            ListNode *next = (ListNode *)removeNode(&keyPtr, &current);
            current = next;
        } else {
            current = current->next; // move to next node
        }
    }
}