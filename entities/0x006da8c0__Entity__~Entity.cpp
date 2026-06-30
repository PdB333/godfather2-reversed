// FUNC_NAME: Entity::~Entity
void __thiscall Entity::~Entity()
{
    // Set vtable to a base class vtable during destruction
    this->vtable = &g_BaseVtable1; // +0x00: vtable pointer

    // Delete sub-object at offset +0xE8
    if (this->m_pSubObject2 != NULL) // param_1[0x3a]
    {
        MemoryDeallocate(this->m_pSubObject2); // FUN_004daf90
    }

    // Delete sub-object at offset +0xE0
    if (this->m_pSubObject1 != NULL) // param_1[0x38]
    {
        MemoryDeallocate(this->m_pSubObject1);
    }

    // Switch vtable to a more base class (finalize destruction)
    this->vtable = &g_BaseVtable2; // +0x00: vtable pointer

    // Clear linked list: head at offset +0x04 (param_1[1])
    ListNode* pNode = this->m_pListHead; // param_1[1]
    while (pNode != NULL)
    {
        ListNode* pNext = pNode->next; // puVar2[1]
        pNode->next = NULL;
        pNode->data = NULL; // *puVar2 = 0
        pNode = pNext;
    }
}