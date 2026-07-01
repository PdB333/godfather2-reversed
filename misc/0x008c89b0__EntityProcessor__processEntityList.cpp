// FUNC_NAME: EntityProcessor::processEntityList
// Address: 0x008c89b0
// Role: Processes a list of entity IDs by calling EntityManager::processEntity on each valid entity not in state 4.
// Field offsets:
//   this+0x08 = bool m_enabled (controls whether processing occurs)
//   entity+0x74 = int32 m_state (state 4 is skipped, e.g., dead or removed)

void __thiscall EntityProcessor::processEntityList(int* entityIds, int count)
{
    EntityManager* manager = nullptr;
    
    // Check if this processor is enabled
    if (*(int32*)((uint8*)this + 8) != 0)
    {
        manager = (EntityManager*)FUN_0043b870(gSimManagerPtr);  // Get singleton
    }
    
    if (count != 0)
    {
        int* currentId = entityIds;
        do
        {
            int entityId = *currentId;
            currentId++;
            
            if (entityId != 0)
            {
                Entity* entity = (Entity*)FUN_009b9c00(entityId);  // Lookup entity by ID
                if (entity != nullptr && *(int32*)((uint8*)entity + 0x74) != 4)  // State is not dead/removed
                {
                    // Call virtual method at vtable offset 0x20 (vtable[8] = EntityManager::processEntity)
                    (*(void(__thiscall**)(Entity*))(*((uint32*)manager) + 0x20))(entity);
                    // In C++: manager->processEntity(entity);
                }
            }
            count--;
        } while (count != 0);
    }
}