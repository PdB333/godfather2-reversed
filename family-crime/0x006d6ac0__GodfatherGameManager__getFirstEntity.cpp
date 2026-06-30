// FUNC_NAME: GodfatherGameManager::getFirstEntity

#include <cstdint>

void* GodfatherGameManager::getFirstEntity() const
{
    // Retrieve pointer to the first node in the intrusive linked list.
    // The head pointer is stored at offset 0x31a8 inside this manager.
    uintptr_t node = *(uintptr_t*)((uint8_t*)this + 0x31a8);
    if (node != 0)
    {
        // Each entity has an embedded list node at offset 0x48 from its base.
        // Subtract 0x48 to get the entity pointer.
        return (void*)(node - 0x48);
    }
    return nullptr;
}