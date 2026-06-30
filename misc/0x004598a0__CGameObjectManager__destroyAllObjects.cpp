// FUNC_NAME: CGameObjectManager::destroyAllObjects
void CGameObjectManager::destroyAllObjects()
{
    int index = 0;
    // Check if there are any fixed objects (array of size 0xB0 each)
    if (this->objectCount != 0) {
        int offset = 0;
        do {
            // Zero out the field at offset 0x4c within each object
            int* objBase = this->objectArrayStart;
            *(int*)(objBase + offset + 0x4c / 4) = 0;
            index = index + 1;
            offset = offset + 0xb0;
        } while (index < this->objectCount);
    }

    // Free linked list of dynamic objects
    ListNode* node = this->dynamicObjectList; // +0x70
    while (node != nullptr) {
        ListNode* nextNode = node->next; // first 4 bytes
        // Assume +8 points to an object that needs cleanup
        FUN_00459280(reinterpret_cast<uint8_t*>(node) + 8);
        // Call global destructor/free on the node itself
        (**(code**)(*DAT_01205868 + 4))(node, 0);
        node = nextNode;
    }
    this->dynamicObjectList = nullptr;
}