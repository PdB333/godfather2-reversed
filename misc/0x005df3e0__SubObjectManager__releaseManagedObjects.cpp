// FUNC_NAME: SubObjectManager::releaseManagedObjects
void SubObjectManager::releaseManagedObjects(void)
{
    // Release managed object at offset 0x10 using manager at offset 0xc
    if (this->m_managed1 != nullptr) {
        // Call vtable[1] on manager1: Release(managed1, deleteFlag=0)
        this->m_manager1->vtable->releaseManaged(this->m_managed1, 0);
        this->m_managed1 = nullptr;
    }
    // Release manager1 itself via vtable[3]
    this->m_manager1->vtable->releaseSelf();

    // Release managed object at offset 0x8 using manager at offset 0x4
    if (this->m_managed0 != nullptr) {
        // Call vtable[1] on manager0: Release(managed0, deleteFlag=0)
        this->m_manager0->vtable->releaseManaged(this->m_managed0, 0);
        this->m_managed0 = nullptr;
    }
    // Release manager0 itself via vtable[3]
    this->m_manager0->vtable->releaseSelf();
}