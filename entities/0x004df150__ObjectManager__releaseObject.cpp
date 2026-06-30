// FUNC_NAME: ObjectManager::releaseObject
// Address: 0x004df150
// Releases a managed object pointer and performs internal cleanup.
void ObjectManager::releaseObject(void) {
    // If the managed object pointer (at +0x00) is not null, deallocate it
    if (this->m_pObject != nullptr) {
        FUN_009c8f10(this->m_pObject);  // custom deallocation (operator delete? free?)
    }
    FUN_009c8eb0();  // engine-level cleanup (shutdown?)
}