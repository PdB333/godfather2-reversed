// FUNC_NAME: GameUtility::raycastWithTargetCheck
// Address: 0x007e92f0
// Description: Casts a ray from start extended beyond end, checks if a point near target is hit,
// filters by mask, and optionally returns the interpolated hit position.

bool __cdecl raycastWithTargetCheck(
    const float* start,            // param_2: ray origin
    const float* end,              // param_3: ray end point (will extend beyond)
    const float* targetPos,        // param_4: position to compare against hit point
    uint collisionType,            // param_5: collision type/category (unused but forwarded?)
    uint collisionMask,            // param_6: bitmask to filter collider flags
    float* outHitPos               // param_7: optional output hit position (interpolated)
) {
    // Direction vector from start to end
    float dirX = end[0] - start[0];
    float dirY = end[1] - start[1];
    float dirZ = end[2] - start[2];

    // Compute squared length of direction vector (FUN_0056afa0 likely returns squared length)
    float dirLenSq = (float)FUN_0056afa0(&dirX, &dirX); // treat as squared length

    // Extend the ray past end by a small offset (global constant, likely 0.001f or similar)
    float extension = dirLenSq + _DAT_00d6fda4;
    float extendedX = dirX * extension + start[0];
    float extendedY = dirY * extension + start[1];
    float extendedZ = dirZ * extension + start[2];

    // Project/query something: FUN_00542650 might be "clampPointOnSegment" or "nearestPointOnLine"
    // param3 = 2 might indicate mode (e.g., segment vs infinite line)
    FUN_00542650(start, &extendedX, 2, collisionType, 0, 0);

    // Prepare collision query context
    // PTR_FUN_00e32a8c is a function pointer table (likely collision query callbacks)
    void* queryContext = &PTR_FUN_00e32a8c;
    int queryResult = 0; // local_70
    float fraction = _DAT_00d5780c; // interpolation factor for hit point
    float hitPos[3]; // local_c0, local_bc, local_b8
    // local_cc is also fraction, but not used? local_cc = _DAT_00d5780c;

    // Perform ray cast or overlap query: FUN_00897310 likely performs a spatial query
    // local_60 is scratch buffer (92 bytes)
    char scratchBuffer[92];
    FUN_00897310(scratchBuffer, &queryContext, 0);

    if (queryResult != 0) {
        // Compare hit position with target position, using a bitwise mask for approximate equality
        // _DAT_00e44680 likely converts float to grid coordinates (e.g., truncation to int)
        uint diffX = (uint)(hitPos[0] - targetPos[0]) & _DAT_00e44680;
        uint diffY = (uint)(hitPos[1] - targetPos[1]) & _DAT_00e44680;
        uint diffZ = (uint)(hitPos[2] - targetPos[2]) & _DAT_00e44680;

        // _DAT_00d5ef84 is tolerance (likely small integer or float interpreted as int?)
        if ((float)diffX <= _DAT_00d5ef84 &&
            (float)diffY <= _DAT_00d5ef84 &&
            (float)diffZ <= _DAT_00d5ef84) {
            // Get collider/entity at hit position
            int entity = FUN_00542700(hitPos);
            if (entity != 0 && (*(uint*)(entity + 4) & collisionMask) != 0) {
                // Optionally output interpolated hit position
                if (outHitPos != nullptr) {
                    outHitPos[0] = (extendedX - start[0]) * fraction + start[0];
                    outHitPos[1] = (extendedY - start[1]) * fraction + start[1];
                    outHitPos[2] = (extendedZ - start[2]) * fraction + start[2];
                }
                return true;
            }
        }
    }
    return false;
}