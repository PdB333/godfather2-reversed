// FUNC_NAME: NodeList::removeByGlobalIndex
bool __fastcall NodeList::removeByGlobalIndex(void* list) {
    bool success = false;
    if (list != nullptr && currentIndex >= 0) {
        Node* node = *(Node**)((int)list + 0x124); // +0x124: head of linked list
        for (int i = 0; i < currentIndex; i++) {
            if (node == nullptr) {
                return false;
            }
            node = node->next; // +0x124: next pointer
        }
        if (node != nullptr) {
            node->flags &= 0xEFFFFFFF; // +0x10: flags, clear bit 28 (e.g., mark inactive)
            success = true;
        }
    }
    return success;
}