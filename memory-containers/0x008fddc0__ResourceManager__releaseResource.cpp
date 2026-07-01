// FUNC_NAME: ResourceManager::releaseResource
void __thiscall ResourceManager::releaseResource(void) {
    // +0xd8: m_pResource (pointer to a resource)
    // +0xdc: m_resourceType (int, maybe 2 for a specific type)
    // +0xd4: m_refCount (int)
    // +0xe0: m_unknown (unknown)
    if (this->m_pResource != nullptr) {
        // Global flag indicating whether resource system is active
        if (DAT_0112a680 != 0) {
            FUN_0094b0e0(this->m_pResource); // resource release (e.g., delete or dec ref)
        }
        if (this->m_resourceType == 2) {
            FUN_004086d0(&DAT_012069c4); // global ref count decrement (or mutex unlock)
            this->m_refCount -= 1;
        }
    }
    // Reset all fields
    this->m_pResource = nullptr;
    this->m_resourceType = 0;
    this->m_unknown = 0;
}