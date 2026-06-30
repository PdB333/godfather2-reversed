// FUNC_NAME: Weapon::calculateAimCorrection
// Address: 0x006cd540
// Role: Computes aim adjustments (lead, screen position) for a given world-space point,
// using a transformation matrix and frame time. Returns a projectile travel time.
// Globals: _DAT_00d5780c (fovScale), _DAT_00d5c458 (screenScale)
// Callees: getAimTransform(0), transformVector(), getFrameTime()

float Weapon::calculateAimCorrection(float* outPos2D, float* outLeadX, float* outLeadY, float* inWorldPoint) {
    // The input vector: inWorldPoint[0..2] = x, y, z
    float local_x = inWorldPoint[0];                     // +0x00
    float local_y = inWorldPoint[1];                     // +0x04
    float local_z = inWorldPoint[2];                     // +0x08 (unused in output but used in transform)
    float fovScale = _DAT_00d5780c;                      // global, possibly FOV or projection scale

    // Get the aiming transform object (likely a per-weapon camera or matrix)
    int transformHandle = getAimTransform(0);            // FUN_004262f0(0) returns handle to a structure
    // Transform the world point into a local space (e.g., view space)
    transformVector(transformHandle, &local_x, &local_x); // in-place transform (FUN_0056b420)

    // Get current frame time delta
    double deltaTime = getFrameTime();                   // FUN_0040c390 returns double

    float frameFov = _DAT_00d5780c;                      // same as fovScale
    float screenScale = _DAT_00d5c458;                   // global, likely screen resolution scale

    // Compute output: normalized 2D position
    outPos2D[0] = local_x / fovScale;                    // Normalized X
    // Y component includes a time-dependent term: denominator = (fovScale - 2*deltaTime) * fovScale
    float denomY = (frameFov - (float)(deltaTime * 2.0f)) * fovScale;
    outPos2D[1] = local_y / denomY;

    // Lead offsets (likely added to aim point for leading moving targets)
    *outLeadX = (local_x / fovScale + frameFov) * screenScale;
    *outLeadY = (local_y / fovScale + frameFov) * screenScale;

    // Return the projectile travel time stored in the transform structure at offset +0x150
    return *(float*)(transformHandle + 0x150);
}