// FUNC_NAME: Entity::GetOwnerFromComponentPointer
inline void* Entity::GetOwnerFromComponentPointer() const
{
    // +0x74c: pointer to a component that is embedded within a parent structure at offset 0x48
    if (this->m_pComponent != nullptr)
        return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this->m_pComponent) - 0x48);
    return nullptr;
}