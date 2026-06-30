// FUNC_NAME: ListNode::incrementTailCounter
short __fastcall ListNode::incrementTailCounter(ListNode* node)
{
    ListNode* currentNode = node;
    // Walk the linked list to the last node (+0x0c = next pointer)
    while (currentNode->next != nullptr) {
        currentNode = currentNode->next;
    }
    // Retrieve old counter value at offset +0x58
    short oldVal = currentNode->counter;
    // Increment the counter and return the previous value
    currentNode->counter = oldVal + 1;
    return oldVal;
}