// FUNC_NAME: SmartPointer::release
void* SmartPointer::release(byte flag) {
    // +0x00: m_ptr - pointer to managed object
    // +0x0C: m_destroyFunc - function pointer to destroy/release the managed object
    if (m_ptr != nullptr) {
        // Call the custom destroy function via pointer at offset 0x0C
        ((void (*)(void*))m_destroyFunc)(m_ptr);
    }
    // If bit 0 of flag is set, deallocate the SmartPointer instance itself
    if ((flag & 1) != 0) {
        operator delete(this);
    }
    return this;
}