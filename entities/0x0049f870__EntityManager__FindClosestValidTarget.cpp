// FUNC_NAME: EntityManager::FindClosestValidTarget
void EntityManager::FindClosestValidTarget(void)
{
    // Get the array of entity pointers and its size from the object.
    // Offset +0x8c: pointer to start of array (Entity**)
    Entity** entityArray = *(Entity***)(this + 0x8c);
    // Offset +0x90: number of entities in the array (int)
    int entityCount = *(int*)(this + 0x90);

    // If the array is empty, return
    if (entityArray != entityArray + entityCount)
    {
        // Global threshold value (likely FLT_MAX or a large distance)
        float closestDistance = DAT_00e2b1a4;
        Entity** current = entityArray;
        Entity** end = entityArray + entityCount;

        do
        {
            Entity* entity = *current;

            // Check if the entity has the 'active' flag at offset 0xb2 (bit 0)
            if (((*(byte*)(entity + 0xb2) & 1) != 0))
            {
                // Get the sub-object at offset 0xa0 (e.g., a health or state component)
                int* subObj = *(int**)(entity + 0xa0);

                // Ensure the sub-object's 'alive' flag at offset 0x34 is not zero
                if (*(int*)(subObj + 0x34) != 0)
                {
                    // Compute distance: subObj->transform->position.z? Actually +0x50 is a pointer to another struct, +0xac is a float (likely distance or vertical position)
                    float distance = *(float*)(*(int*)(subObj + 0x50) + 0xac);

                    if (distance < closestDistance)
                    {
                        closestDistance = distance;
                    }
                }
            }

            current++;
        } while (current != end);
    }

    // Note: The found minimum distance is not stored or returned.
    // This may be a vestigial function or the caller accesses a global/this member that was omitted during decompilation.
    return;
}