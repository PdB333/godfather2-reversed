// FUNC_NAME: StreamManager::destructor
void __fastcall StreamManager::destructor(StreamManager* this) {
    // Set vtable to current class vtable (likely already set)
    this->vtable = &StreamManager_vtable_00e3abdc;

    // Call manager->releaseStream(handle, 0)
    // m_pManager is at offset 4, m_nHandle at offset 32
    this->m_pManager->releaseStream(this->m_nHandle, 0);

    // If m_pChild is non-null, release it as well
    if (this->m_pChild != nullptr) {
        g_pManager = this->m_pManager; // Store manager globally for the call
        // m_pChild points to an object with a 4-byte header (e.g., reference count)
        // Subtract 4 to get the actual object pointer
        this->m_pManager->releaseStream(reinterpret_cast<int*>(this->m_pChild) - 1, 0);
        g_pManager = this->m_pManager; // Restore (redundant but matches binary)
    }

    // Call manager->stopAll()
    this->m_pManager->stopAll();

    // Change vtable to base class vtable (destructor chaining)
    this->vtable = &StreamManager_base_vtable_00e3abe0;

    // Decrement global active count
    g_bActive = 0;
}