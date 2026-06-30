// FUNC_NAME: BaseClass::cleanup
void __fastcall BaseClass::cleanup(BaseClass* this)
{
    // Set virtual table pointer to base class vtable (destructor chain)
    this->vtable = &PTR_LAB_00d63090; // +0x00: Base vtable

    // Check if sub-object at offset 0x68 exists
    if (this->m_subObject != nullptr) {
        // Destroy the sub-object
        subObjectDestructor(this->m_subObject);
    }

    // Perform global cleanup (likely debug/logging)
    globalCleanupFunction();
}