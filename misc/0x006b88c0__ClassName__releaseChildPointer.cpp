// FUNC_NAME: ClassName::releaseChildPointer
// Address: 0x006b88c0
// Role: Cleanup/destructor helper that releases a dynamically allocated child object at offset 0x98

// Assumes the class has a pointer member at +0x98 to an object that is freed by FUN_009c8eb0 (likely operator delete or custom destructor)
void __thiscall ClassName::releaseChildPointer() {
    // Check if the child pointer is non-null
    if (this->m_pChild != nullptr) {
        // Release the child object (likely calls its destructor or deallocates)
        FUN_009c8eb0(this->m_pChild); // +0x98: pointer to child object
        // Set pointer to null to avoid dangling
        this->m_pChild = nullptr;
    }
    return;
}