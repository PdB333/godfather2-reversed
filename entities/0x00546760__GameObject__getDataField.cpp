// FUNC_NAME: GameObject::getDataField
// Function at 0x00546760: retrieves a 4-byte value from a data block pointed to by this+0x2e8 at offset 0x10.
uint32_t __thiscall GameObject::getDataField(void) const
{
    // Dereference pointer at this+0x2e8 (likely m_pDataBlock), then read uint32 at offset 0x10 (some field)
    return *(uint32_t*)(*(uint32_t*)((uint32_t)this + 0x2e8) + 0x10);
}