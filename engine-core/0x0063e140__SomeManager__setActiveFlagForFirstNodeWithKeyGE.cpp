// FUNC_NAME: SomeManager::setActiveFlagForFirstNodeWithKeyGE

void __fastcall SomeManager::setActiveFlagForFirstNodeWithKeyGE(int threshold)
{
    ListNode *curNode = *(ListNode**)(this + 0x14); // head of linked list at +0x14
    if (curNode == nullptr) {
        return;
    }
    // Walk sorted list until we find a node with key >= threshold
    while (threshold < curNode->key) {
        curNode = curNode->next; // +0x00 next pointer
        if (curNode == nullptr) {
            return;
        }
    }
    // Set flag at +0x0C to 1 (active/selected)
    curNode->flag = 1;
}