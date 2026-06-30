// FUNC_NAME: BNKStreamManager::~BNKStreamManager
void __thiscall BNKStreamManager::~BNKStreamManager(BNKStreamManager* this) // 0x007633b0
{
    BNKStreamNode* node;
    BNKStreamNode* next;

    // Set vtable to destructor vtable
    this->vfptr = (void**)&LAB_d65584; // +0x00
    this->m_pStreamVtable = (void**)&LAB_d65580; // +0x50

    // Destroy sub‑stream at offset 0x58
    if (this->m_pSubStream != nullptr) // +0x58
    {
        StreamManager::stopStream(0x45); // 0x007f6420
        // Clear flags in the sub‑object at +0x78
        uint flags1 = *(uint*)(this->m_pSubObject + 0xb4); // +0x78 -> +0xb4
        *(uint*)(this->m_pSubObject + 0xb4) = flags1 & 0xfffffbff;
        // Reset function pointer in sub‑object
        *(void***)(this->m_pSubObject + 0xa0) = FUN_005fe070; // callback
        uint flags2 = *(uint*)(this->m_pSubObject + 0x114);
        *(uint*)(this->m_pSubObject + 0x114) = flags2 & 0xfffffff7;
    }

    // Release secondary resource at +0xd8
    if (this->m_pSecondaryResource != nullptr) // +0xd8
    {
        BNKStreamManager::shutdown(); // 0x009b4760
    }

    // Release object pointer at +0x68
    if (this->m_pObject1 != nullptr) // +0x68
    {
        operator delete(this->m_pObject1); // 0x004daf90
    }

    // Release object pointer at +0x5c
    if (this->m_pObject2 != nullptr) // +0x5c
    {
        operator delete(this->m_pObject2); // 0x004daf90
    }

    // Reset stream vtable
    this->m_pStreamVtable = (void**)&FUN_00e32808; // +0x50

    // Free the linked list of BNK stream nodes starting at +0x54
    node = this->m_pStreamNodeList; // +0x54
    while (node != nullptr)
    {
        next = node->next; // +0x04
        node->next = nullptr;
        node->data = nullptr; // +0x00
        node = next;
    }

    // Global cleanup
    SharedCleanup(); // 0x004ac1e0
}