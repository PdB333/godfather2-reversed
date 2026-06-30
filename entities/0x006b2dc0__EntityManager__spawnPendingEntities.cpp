// FUNC_NAME: EntityManager::spawnPendingEntities
void EntityManager::spawnPendingEntities()
{
    uint32_t index = 0;

    if (this->m_objectCount != 0) {
        do {
            // m_objects is a pointer to an array of pointers (e.g., Entity**)
            Entity* entity = this->m_objects[index];

            // Check if entity's flags byte at offset 0x5f has bit 0 clear (e.g., not alive/spawned)
            if (((entity->flagsAt0x5f & 1) == 0) && 
                (iVar1 = /* 0x00791300 */ allocateObject(), iVar1 != nullptr)) {
                // iVar1 is pointer to newly allocated object (e.g., a component or entity)
                // Call constructor for sub-object at offset 0x3c
                /* 0x004088c0 */ initializeSubObject(iVar1 + 0x3c);
            }

            index++;
        } while (index < this->m_objectCount);
    }
}