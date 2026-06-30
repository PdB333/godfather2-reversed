// FUNC_NAME: LinkedListContainer::clearList
void LinkedListContainer::clearList(void)
{
    // +0x00: vtable pointer
    // +0x04: pointer to first node in linked list (head)
    // Each node:
    //   +0x00: previous pointer
    //   +0x04: next pointer?
    //   +0x08: data or another link?
    // Here we set vtable then iterate through list and zero out each node's fields.
    this->vtable = &PTR_LAB_00e42de4;

    ListNode* currentNode = this->head;
    while (currentNode != nullptr) {
        ListNode* nextNode = currentNode->next;  // offset +0x08
        currentNode->prev = nullptr;              // offset +0x00
        currentNode->data = nullptr;              // offset +0x04
        currentNode->next = nullptr;              // offset +0x08
        currentNode = nextNode;
    }
}