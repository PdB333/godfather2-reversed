// FUNC_NAME: CoverHintNodeManager::findClosestCoverPoint
// Address: 0x00874ce0
// Finds the closest cover hint node to a given position, considering a radius around each node.
// The nodes are stored in a small array of 3 pointers at offset 0xcb4 from this.
// The function uses the player's Y coordinate (from a global singleton) as the vertical reference for nodes.

int __thiscall CoverHintNodeManager::findClosestCoverPoint(const float* position, float* outClosestPoint, float* outDistanceSq)
{
    int closestNode = 0;
    float bestDistSq = *(float*)0x00d764dc; // Large initial value from debug string constant

    // Get player object (or camera) to read Y coordinate at offset 0x34
    int* player = FUN_00471610(); // e.g., getPlayer()
    float playerY = *(float*)(player + 0x34); // Player's Y position

    // Iterate over the 3 cover hint node slots
    int* nodePtrArray = (int*)(this + 0xcb4);
    for (int i = 0; i < 3; i++)
    {
        int node = nodePtrArray[i];
        if (node != 0)
        {
            // Read node data: position (x, z) and radius
            float nodeX = *(float*)(node + 0x10);
            float nodeZ = *(float*)(node + 0x14); // Note: stored as Y in memory but used as Z
            float nodeRadius = *(float*)(node + 0x18);

            // Compute direction from node to the given position, using playerY for vertical component
            float dirX = position[0] - nodeX;
            float dirY = position[1] - playerY; // Use player's Y as reference
            float dirZ = position[2] - nodeZ;

            // Normalize the direction vector
            vectorNormalize(&dirX, &dirX); // In-place normalization

            // Compute target point on the node's sphere (or circle) closest to the position
            float targetX = dirX * nodeRadius + nodeX;
            float targetY = dirY * nodeRadius + playerY; // Keep Y consistent with player
            float targetZ = dirZ * nodeRadius + nodeZ;

            // Compute squared distance from position to target point
            float dx = targetX - position[0];
            float dy = targetY - position[1];
            float dz = targetZ - position[2];
            float distSq = dx*dx + dy*dy + dz*dz;

            // Keep the closest node
            if (distSq <= bestDistSq)
            {
                closestNode = node;
                bestDistSq = distSq;
                if (outClosestPoint != 0)
                {
                    outClosestPoint[0] = targetX;
                    outClosestPoint[1] = targetY;
                    outClosestPoint[2] = targetZ;
                }
            }
        }
    }

    if (outDistanceSq != 0)
    {
        *outDistanceSq = bestDistSq;
    }
    return closestNode;
}