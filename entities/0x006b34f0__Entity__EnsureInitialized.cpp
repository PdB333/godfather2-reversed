// FUNC_NAME: Entity::EnsureInitialized
// Function address: 0x006b34f0
// Role: Lazy initialization check - initializes internal component if not already done.

void Entity::EnsureInitialized()
{
    if (this->m_pComponent == 0) // +0x16c: pointer to internal component (or initialization flag)
    {
        this->Initialize(); // FUN_006b3390: internal initializer
    }
}