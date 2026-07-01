// FUNC_NAME: EARSFrameworkObject::shutdown
bool __fastcall EARSFrameworkObject::shutdown(FrameworkObject* this) {
    // Set shutdown flag at offset 0x380
    this->m_shutdownFlag = 1; // +0x380

    // If there's a cleanup handler at offset 0xc, invoke its virtual cleanup function
    if (this->m_pCleanupHandler != nullptr) { // +0xc
        // Call the first virtual function (likely Release or Destroy) through the vtable
        this->m_pCleanupHandler->Release(); // equivalent to (**(code**)*(this+0xc))()
        this->m_pCleanupHandler = nullptr; // +0xc cleared
    }

    return true; // success
}