// FUNC_NAME: ObjectList::clearAndDeleteAll
void ObjectList::clearAndDeleteAll()
{
    // this->listHead at offset 0x18 (embedded sentinel node)
    ListNode* head = this->listHead;
    ListNode* node = head->next; // first actual node

    // Remove all nodes by making sentinel point to itself (empty list)
    head->next = head;
    head->prev = head;
    this->count = 0; // offset 0x1C

    // Delete each node via vtable[1] (destructor + custom deallocation)
    while (node != head)
    {
        ListNode* nextNode = node->next;
        // Call vtable[1] (offset 4) with node and size 0xc (12 bytes, object size)
        node->vtable->destroy(node, 0xc);
        node = nextNode;
    }
}