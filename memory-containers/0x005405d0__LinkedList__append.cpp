// FUNC_NAME: LinkedList::append
void __thiscall LinkedList::append(int this, void* data) {
    ListNode* head = *(ListNode**)(this + 0x44); // linked list head
    if (head != nullptr) {
        ListNode* current = head;
        ListNode* next = current->next;
        // traverse to the end of the list
        while (next != nullptr) {
            current = next;
            next = current->next;
        }
        // allocate new node (8 bytes: 4 for data, 4 for next pointer)
        ListNode* newNode = (ListNode*)FUN_009c8e50(8);
        newNode->next = nullptr;
        newNode->data = data;
        current->next = newNode; // link at the end
    } else {
        // empty list: allocate new head node
        ListNode* newNode = (ListNode*)FUN_009c8e50(8);
        newNode->next = nullptr;
        newNode->data = data;
        *(ListNode**)(this + 0x44) = newNode;
    }
    // increment count at +0x48
    *(int*)(this + 0x48) = *(int*)(this + 0x48) + 1;
}