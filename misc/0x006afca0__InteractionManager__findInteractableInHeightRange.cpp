// FUNC_NAME: InteractionManager::findInteractableInHeightRange
// Function: 0x006afca0
// Reconstructed from Ghidra decompilation. Likely performs a vertical range query to find an interactable entity.
// Parameters:
//   position: pointer to Vector3 (x, y, z) of the query origin
//   upOffset: positive vertical range above position
//   downOffset: negative vertical range below position
//   outEntity: output pointer to entity ID (at offset +0x1DC of component)
//   outIsInteractable: output byte set to 1 if the entity has a specific flag (0x4000)
// Returns 1 if any entity found matching criteria, 0 otherwise.

int __cdecl findInteractableInHeightRange(Vector3* position, float upOffset, float downOffset, int* outEntity, char* outIsInteractable) {
    uint resultBits;
    int entityHandle;
    int queryResult;
    int entityPtr;
    int componentPtr;

    // Initialize outputs
    *outEntity = 0;
    *outIsInteractable = 0;

    // Build bounding box: from (x, y - downOffset, z) to (x, y + upOffset, z)
    // The box is a vertical line segment (no x or z change)
    float boxMinY = position->y + upOffset;
    float boxMaxY = position->y - downOffset;
    Vector3 boxMin = { position->x, boxMinY, position->z };
    Vector3 boxMax = { position->x, boxMaxY, position->z };

    // Perform spatial query (likely AABB overlap test)
    // Parameters: boxMin, boxMax, queryType=2, flags=0x80000000, unk1=0, unk2=0
    SpatialQuery::testAABBOverlap(&boxMin, &boxMax, 2, 0x80000000, 0, 0);

    // Setup query result structure
    int queryFlags = 0xFFFFFFFF; // -1
    int queryResult2 = 0xFFFFFFFF;
    int globalData = DAT_00d5780c; // Global pointer for query context
    int queryState = 0;
    entityHandle = 0;

    // Create query key (16 bytes) and initialize query
    // local_c0 is a 16-byte UUID/guid for the query
    char queryKey[16]; // Could be from a constant or derived
    SpatialQuery::createQuery(queryKey, queryState); // Actually FUN_009e69d0 writes to queryState from local_60? Need to match

    // If query produced results (entityHandle != 0)
    if (entityHandle != 0) {
        // Get first result from the query
        queryResult = SpatialQuery::getFirstResult(queryKey);
        if (queryResult != 0) {
            resultBits = *(uint*)(queryResult + 4); // Result flags at offset +4
            // Check if entity has category flags (0x30000 = maybe "interactable" or "trigger")
            if ((resultBits & 0x30000) != 0) {
                // If entity also has sub-flags (0x4800 = maybe "pickup" or "collectible")
                if ((resultBits & 0x4800) != 0 && entityHandle != 0) {
                    // Get the actual entity object from handle
                    entityPtr = EntityManager::getEntityFromHandle(entityHandle);
                    // Look for a specific component by hash (0xf5d7aeff = likely "InteractionComponent")
                    componentPtr = Entity::getComponentByHash(entityPtr, 0xf5d7aeff);
                    if (componentPtr != 0) {
                        int entityID = *(int*)(componentPtr + 0x1DC); // +0x1DC: presumably entity ID or target ID
                        *outEntity = entityID;
                        // If entity also has a special flag (0x4000 = maybe "active" or "enabled")
                        if ((resultBits & 0x4000) != 0) {
                            *outIsInteractable = 1;
                        }
                        return 1;
                    }
                }
                return 1; // Entity found but not fully interactable
            }
        }
    }
    return 0; // No matching entity
}