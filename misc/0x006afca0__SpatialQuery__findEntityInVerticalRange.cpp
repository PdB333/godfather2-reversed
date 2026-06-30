// FUNC_NAME: SpatialQuery::findEntityInVerticalRange

#include <cstdint>

// Performs a spatial overlap query (cylinder or AABB) to find an entity of a specific type within a vertical range.
// param_1: pointer to a vec3 center (x, y, z)
// param_2: positive upward offset from center Y
// param_3: positive downward offset from center Y (subtracted from Y)
// param_4: output int pointer to receive the entity ID (likely a handle or index) if found
// param_5: output byte pointer, set to 1 if the found entity has a specific sub-flag (0x4000)
// Returns 1 if an entity was found matching the criteria, 0 otherwise.
int SpatialQuery::findEntityInVerticalRange(int* param_1, float param_2, float param_3, int* param_4, char* param_5)
{
    int* queryResult;          // local_c0 (16-byte result from overlap query)
    char queryInput[92];       // local_60 (input struct for the query)
    int resultHandle;          // local_70 (handle or index from query)
    int entityId;              // temp for reading entity ID
    uint flags;                // flags from an entity structure
    int entityPtr;             // entity pointer returned by other functions
    int ownerPtr;              // owner / container pointer
    int componentPtr;          // component pointer from hash lookup
    int finalEntityId;         // the entity ID to output

    // Clear outputs
    *param_4 = 0;
    *param_5 = 0;

    // Build two point positions: top and bottom of the vertical range (same X and Z, different Y)
    // param_1 layout: [0]=float x, [1]=float y, [2]=float z (the parameters are word-aligned, cast to float*)
    float centerX = *(float*)¶m_1[0];
    float centerY = *(float*)¶m_1[1];
    float centerZ = *(float*)¶m_1[2];

    float topY = centerY + param_2;
    float bottomY = centerY - param_3;

    // Setup a cylindrical or AABB shape from the two points
    // FUN_005425d0 is likely "setupShapeFromPoints" 
    // Arguments: &topPoint, &bottomPoint, count=2, flags=0x80000000, unknown1=0, unknown2=0
    setupShapeFromPoints(centerX, topY, centerZ, centerX, bottomY, centerZ, 2, 0x80000000, 0, 0);

    // Initialize query parameters
    int unknown1 = -1;       // local_ac
    int unknown2 = -1;       // local_a0
    int globalManager = _DAT_00d5780c; // local_b0: probably a singleton manager or physics object pointer
    int unknown3 = 0;        // local_80
    resultHandle = 0;        // clear handle

    // Perform the overlap query (e.g., find all entities intersecting the shape)
    // FUN_009e69d0 likely takes an input buffer (queryInput) and an output buffer (queryResult)
    performOverlapQuery(queryInput, &queryResult); // modifies queryResult and resultHandle

    // Check if a result was obtained
    if (resultHandle != 0)
    {
        // Extract the first (or only) result from the query output
        // FUN_00542700 likely extracts a pointer or handle from the query result struct
        entityPtr = getEntityFromResult(&queryResult);

        if (entityPtr != 0)
        {
            // Read flags at offset +4 from the entity structure
            flags = *(uint*)(entityPtr + 4);

            // Check if entity belongs to a main category (bits 0x30000)
            if ((flags & 0x30000) != 0)
            {
                // Check for sub-categories (bits 0x4800)
                if (((flags & 0x4800) != 0) && (resultHandle != 0))
                {
                    // Get the owner/container from the result handle (FUN_004afca0)
                    ownerPtr = getOwnerFromResult(resultHandle);

                    // Lookup a component within the owner by a hash (0xf5d7aeff)
                    // FUN_006af9b0 likely returns a component pointer matching the hash
                    componentPtr = getComponentByHash(ownerPtr, 0xf5d7aeff);

                    if (componentPtr != 0)
                    {
                        // Read entity ID from the component at offset 0x1dc
                        finalEntityId = *(int*)(componentPtr + 0x1dc);
                        *param_4 = finalEntityId;

                        // If entity ID is valid and the entity has a specific flag (0x4000) set
                        if ((finalEntityId != 0) && ((flags & 0x4000) != 0))
                        {
                            *param_5 = 1;   // Indicate special sub-type
                        }
                    }
                    return 1;
                }
                return 1;   // Found entity but didn't match sub-criteria
            }
        }
    }
    return 0;   // No entity found
}