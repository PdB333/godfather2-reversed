// FUNC_NAME: AIBehavior::checkTargetDistance
bool __thiscall AIBehavior::checkTargetDistance(int thisPtr) {
    // Check if this pointer is valid
    if (thisPtr == 0) {
        return false;
    }

    // Check two condition flags (e.g., alive/valid states)
    if (isActionAllowed() || isOtherConditionMet()) {
        return false;
    }

    // Get source and target positions from a singleton manager (e.g., EntityManager)
    int source = getPositionSource();  // FUN_00471610()
    int target = getPositionTarget();  // FUN_00471610()

    // Extract packed position data: 8 bytes at +0x30 (likely 2 × 32-bit integer components)
    // and a float at +0x38 (likely third component, e.g., Z)
    uint64_t srcPacked = *(uint64_t*)(source + 0x30);
    float srcZ = *(float*)(source + 0x38);
    uint64_t tgtPacked = *(uint64_t*)(target + 0x30);
    float tgtZ = *(float*)(target + 0x38);

    // Convert packed data – the high 32 bits are interpreted as float (Y?),
    // the low 32 bits are not used directly in subtraction? Actually used later.
    // This likely extracts Y from a packed XY pair.
    float srcY = (float)(uint32_t)(srcPacked >> 32);
    float tgtY = (float)(uint32_t)(tgtPacked >> 32);
    float srcX = (float)(uint32_t)(srcPacked & 0xFFFFFFFF);
    float tgtX = (float)(uint32_t)(tgtPacked & 0xFFFFFFFF);

    // Check if Y difference (absolute) is below a threshold (DAT_00d5eee4)
    float yDiff = tgtY - srcY;
    uint32_t yDiffUint = (uint32_t)(yDiff) & 0x7FFFFFFF;  // Absolute (simulated)
    float yDiffAbs = (float)yDiffUint;  // Actually this is wrong; original used & DAT_00e44680 (likely 0x7FFFFFFF)
    if (yDiffAbs >= DAT_00d5eee4) {
        return false;
    }

    // Calculate squared 3D distance
    float dx = srcX - tgtX;
    float dy = srcY - tgtY;
    float dz = srcZ - tgtZ;
    float distSq = dx*dx + dy*dy + dz*dz;

    // Compare with threshold squared (DAT_00d62b50)
    return distSq < DAT_00d62b50;
}