// FUNC_NAME: CoverHintNodeManager::collectCoverNodesInRange
// Function at 0x007a8630: Collects cover nodes within range, checks line-of-sight and validity, stores results in a dynamic array sorted by distance from a reference point.

int CoverHintNodeManager::collectCoverNodesInRange(
    bool ignoreVisibilityCheck,
    Vector3* outPositions,          // Output buffer for world positions (each entry: x,y,z,distSq)
    DynamicArray<int16_t>* nodeArray, // Dynamic array descriptor: base ptr, count, capacity (each entry 16 bytes)
    uint32_t nodeCount,             // Number of candidate nodes to test
    CoverHintNodeManager* manager   // +0x30c8 holds a scale factor (e.g., radius)
)
{
    // Get pointers to global transforms (likely camera and player position)
    Transform* camTransform = getCameraTransform();
    Transform* playerTransform = getPlayerTransform();

    int validCount = 0;
    uint32_t nodeIndex = 0;
    int insertedCount = 0;

    if (nodeCount == 0)
        return 0;

    do {
        // Each candidate is identified by a bitmask (1 << nodeIndex)
        uint32_t nodeBit = 1 << (nodeIndex & 0x1f);

        // Get the node's local direction and reference point (fills local_c, local_8, local_4 as direction vector)
        Vector3 direction;
        getNodeDirection(nodeBit, &direction);

        // Scale factor from manager (e.g., collider radius or range)
        float scale = *(float*)((uint32_t)manager + 0x30C8);

        // Compute world space position: camera position + direction * scale
        Vector3 worldPos;
        worldPos.x = direction.x * scale + *(float*)((uint32_t)camTransform + 0x30);
        worldPos.y = direction.y * scale + *(float*)((uint32_t)camTransform + 0x34);
        worldPos.z = direction.z * scale + *(float*)((uint32_t)camTransform + 0x38);

        // Condition: if ignoring visibility check, or line-of-sight check passes
        bool lineOfSightOK = ignoreVisibilityCheck || isPointVisible(&worldPos, 1, 1);
        bool nodeValid = isNodeActive(nodeBit) || isNodeOccupied(nodeBit, 0);

        if (lineOfSightOK && nodeValid) {
            // Store world position to output buffer (first 3 floats, then squared distance to player)
            outPositions->x = worldPos.x;
            outPositions->y = worldPos.y;
            outPositions->z = worldPos.z;

            // Compute squared distance from player position
            Vector3 diff;
            diff.x = worldPos.x - *(float*)((uint32_t)playerTransform + 0x30);
            diff.y = worldPos.y - *(float*)((uint32_t)playerTransform + 0x34);
            diff.z = worldPos.z - *(float*)((uint32_t)playerTransform + 0x38);
            outPositions->distSq = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;

            // Dynamic array growth if full
            if (nodeArray->count == nodeArray->capacity) {
                int newCapacity = (nodeArray->capacity == 0) ? 1 : nodeArray->capacity * 2;
                growArray(newCapacity);
            }

            // Append entry to dynamic array (each entry 16 bytes)
            uint8_t* entryPtr = (uint8_t*)(nodeArray->base) + nodeArray->count * 16;
            *(Vector3*)entryPtr = *outPositions;
            nodeArray->count++;

            validCount++;
            outPositions++; // advance by 16 bytes (Vector3 with distSq)
        }

        nodeIndex++;
        insertedCount = validCount; // or keep using validCount for return
    } while (nodeIndex < nodeCount);

    return validCount;
}