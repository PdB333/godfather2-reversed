// FUNC_NAME: Navigation::testPointOnNavMesh
bool Navigation::testPointOnNavMesh()
{
    // Check if navigation system is active
    char isActive = Navigation::isSystemActive();  // FUN_007eeb00
    if (!isActive) {
        // If system not active, assume point is valid
        return true;
    }

    // Get a pointer to a transform or vector (likely from world data)
    uint64_t* pWorldData = (uint64_t*)Navigation::getWorldData();  // FUN_00471610

    // Extract two floats from the packed 64-bit value (low = X, high = Y)
    float xOffset = (float)pWorldData[0];                        // low 32 bits
    float yOffset = (float)(pWorldData[0] >> 32);                // high 32 bits
    // Next 8 bytes (pWorldData+1) contain a float (likely Z component)
    float zOffset = *(float*)(pWorldData + 1);                   // +8 offset

    // Apply world scaling factor
    float scaledX = xOffset * worldScale;   // DAT_00d65c68
    float scaledY = yOffset * worldScale;
    float scaledZ = zOffset * worldScale;

    // Get a second pointer (likely to the player or camera transform)
    int transformPtr = Navigation::getWorldData();  // second call returns different object
    // Read position from offset 0x30 (48 bytes) in that transform
    float baseX = *(float*)(transformPtr + 0x30);
    float baseY = *(float*)(transformPtr + 0x34);
    float baseZ = *(float*)(transformPtr + 0x38);

    // Compute target point by adding scaled offset to base position
    float targetX = baseX + scaledX;
    float targetY = baseY + scaledY;
    float targetZ = baseZ + scaledZ;

    // Get third pointer (likely to navmesh or collision system)
    int navPtr = Navigation::getWorldData();
    // Test if the calculated point is on the navmesh
    // Returns 0 if point is valid (on navmesh)
    char result = Navigation::testPointOnMesh(navPtr + 0x30, &targetX, 0, 0, 0);  // FUN_0054eb70

    return (result == 0);
}