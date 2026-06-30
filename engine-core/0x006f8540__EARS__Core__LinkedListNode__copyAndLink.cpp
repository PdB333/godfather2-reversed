// FUNC_NAME: EARS::Core::LinkedListNode::copyAndLink
struct ListNode {
    uint32_t field0;      // +0x00: some data
    ListNode* link1;      // +0x04: pointer to a node in list1
    ListNode* next1;      // +0x08: next pointer in list1
    ListNode* link2;      // +0x0C: pointer to a node in list2
    ListNode* next2;      // +0x10: next pointer in list2
    uint32_t field5;      // +0x14: unknown, zeroed
    uint32_t field6;      // +0x18: unknown, zeroed
};

void __thiscall ListNode::copyAndLink(ListNode* thisNode, ListNode* sourceNode)
{
    // Copy data and first link pointer
    thisNode->field0 = sourceNode->field0;
    thisNode->link1 = sourceNode->link1;
    thisNode->next1 = NULL;

    // Insert into first linked list: update the node pointed to by link1
    ListNode* pLink1 = sourceNode->link1;
    if (pLink1 != NULL) {
        thisNode->next1 = pLink1->next1;  // Adopt the next pointer from the linked node
        // The linked node's next pointer now points to this node's link1 field (self-referential)
        pLink1->next1 = &(thisNode->link1);
    }

    // Handle second linked list (identical pattern)
    thisNode->link2 = sourceNode->link2;
    thisNode->next2 = NULL;
    ListNode* pLink2 = sourceNode->link2;
    if (pLink2 != NULL) {
        thisNode->next2 = pLink2->next2;
        pLink2->next2 = &(thisNode->link2);
    }

    // Clear remaining fields
    thisNode->field5 = 0;
    thisNode->field6 = 0;
}