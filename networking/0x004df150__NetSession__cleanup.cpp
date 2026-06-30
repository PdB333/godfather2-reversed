// FUNC_NAME: NetSession::cleanup
void __thiscall NetSession::cleanup(void) {
    // If the internal resource pointer is non-null, free it
    if (this->m_pResource != nullptr) {
        Memory::deallocate(this->m_pResource);
    }
    // Perform final cleanup (e.g., releasing memory pools or calling base destructor)
    Memory::cleanup();
}