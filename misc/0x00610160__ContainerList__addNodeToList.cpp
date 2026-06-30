// FUNC_NAME: ContainerList::addNodeToList
void __thiscall ContainerList::addNodeToList(ContainerList *this, ListNode *node)
{
    // +0x84: head pointer (next)
    // +0x88: prev pointer
    // +0x8c: next pointer
    // +0x80: container pointer (parent)
    node->prev = this->head;                // param_2 + 0x88 = param_1 + 0x84
    node->next = 0;                         // param_2 + 0x8c = 0
    if (this->head != 0) {
        this->head->next = node;            // *(+0x8c) at head = node
    }
    this->head = node;                      // param_1 + 0x84 = param_2
    node->container = this;                 // param_2 + 0x80 = param_1
    FUN_006101b0();                         // post-insert callback
    return;
}