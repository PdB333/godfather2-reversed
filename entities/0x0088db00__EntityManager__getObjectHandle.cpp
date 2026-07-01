// FUNC_NAME: EntityManager::getObjectHandle
uint32_t __thiscall EntityManager::getObjectHandle(int index)
{
    // Retrieves a 32-bit value from an object pointer table stored at offset 0x80.
    // The table is an array of handles (e.g., entity IDs or pointers) indexed by 'index'.
    return *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x80 + index * 4);
}