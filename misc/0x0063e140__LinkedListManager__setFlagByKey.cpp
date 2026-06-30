// FUNC_NAME: LinkedListManager::setFlagByKey
void __fastcall LinkedListManager::setFlagByKey(int key) {
    int* node = *(int**)(this + 0x14); // +0x14: head of sorted linked list
    if (node != nullptr) {
        // Traverse list while key is less than node's key (node[2] at +0x08)
        while (key < node[2]) {
            node = (int*)*node; // +0x00: next pointer
            if (node == nullptr)
                return;
        }
        // Found node where key >= node->key; set flag at +0x0C to 1
        node[3] = 1; // +0x0C: flag field
    }
}