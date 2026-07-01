// FUNC_NAME: Entity::~Entity
void __thiscall Entity::~Entity(void)
{
    // +0x00: vtable pointer
    this->vtable = &PTR_LAB_00d63090;  // Restore vtable to this class (prevent virtual calls during destruction)
    
    // +0x68: pointer to a subobject (e.g., m_pComponent or m_pData)
    if (this->m_pSubObject != nullptr)
    {
        // Call helper that deletes the subobject and nulls the pointer
        deleteSubObject(&this->m_pSubObject);  // FUN_004daf90
    }
    
    // Perform base class cleanup (e.g., free memory or call ~Object)
    baseCleanup();  // FUN_0080ea60
}