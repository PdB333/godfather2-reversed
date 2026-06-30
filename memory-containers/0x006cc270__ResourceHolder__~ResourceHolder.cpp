// FUNC_NAME: ResourceHolder::~ResourceHolder
void __thiscall ResourceHolder::~ResourceHolder(ResourceHolder* this)
{
    if (this->m_pResource2 != nullptr) {
        // FUN_004daf90: likely operator delete or custom deallocator
        delete this->m_pResource2; // offset +8: second owned resource
    }
    if (this->m_pResource1 != nullptr) {
        delete this->m_pResource1; // offset 0: first owned resource
    }
    // Note: member at offset +4 (e.g., m_count) not freed here
    return;
}