// FUNC_NAME: Entity::setLinkedObject
void __thiscall Entity::setLinkedObject(Entity* this, Entity* targetObject, byte flags)
{
    // OR flags into the byte at offset 0x04 (e.g., m_controlFlags)
    *(byte*)((uintptr_t)this + 4) |= flags;

    // Copy the value at targetObject->field_0x40 (e.g., m_linkedRef) into this->field_0x00 (e.g., m_linkedObjectID)
    *(uint32_t*)this = *(uint32_t*)((uintptr_t)targetObject + 0x40);
}