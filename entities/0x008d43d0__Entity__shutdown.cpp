// FUNC_NAME: Entity::shutdown
void __thiscall Entity::shutdown(Entity *this)
{
    // Check if the sub-object pointer at offset +0x64 is non-null
    if (this->m_pSubObject != nullptr) {
        // Call the virtual function at vtable offset 0x18 (index 6) on the sub-object
        // This is likely a release or cleanup method
        this->m_pSubObject->vtable[6]();
    }
    // Set the active flag at offset +0x60 to false
    this->m_bActive = false;
}