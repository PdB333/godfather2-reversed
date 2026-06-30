// FUNC_NAME: ResourceContainer::releaseAll
void ResourceContainer::releaseAll() {
    if (this->m_nCount == 0) {
        return;
    }

    int count = this->m_nCount;
    // Iterate through items in reverse order
    for (int i = count - 1; i >= 0; --i) {
        int itemOffset = i * 0x34;  // Each item is 0x34 bytes
        char* itemBase = reinterpret_cast<char*>(this->m_pArray) + itemOffset;

        // Offset +0x0C: first resource pointer
        int* pRes1 = *reinterpret_cast<int**>(itemBase + 0x0C);
        if (pRes1 != nullptr) {
            FUN_009c8f10(pRes1);  // Release or delete resource
        }

        // Offset +0x18: second resource pointer
        int* pRes2 = *reinterpret_cast<int**>(itemBase + 0x18);
        if (pRes2 != nullptr) {
            FUN_009c8f10(pRes2);
        }

        // Offset +0x24: third resource pointer
        int* pRes3 = *reinterpret_cast<int**>(itemBase + 0x24);
        if (pRes3 != nullptr) {
            FUN_009c8f10(pRes3);
        }
    }

    this->m_nCount = 0;
}