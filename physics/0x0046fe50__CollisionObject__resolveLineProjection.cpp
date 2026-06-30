// FUNC_NAME: CollisionObject::resolveLineProjection
void __thiscall CollisionObject::resolveLineProjection(float *point, float *direction) {
    // Global constants (addresses from Ghidra)
    static float *g_defaultDirection = (float *)0x00e2e358;
    static float g_floatUnused0 = *(float *)0x00e2b1a4; // local_14 init, unused
    static float g_scaleFactor = *(float *)0x00e2eff4;   // DAT_00e2eff4
    static float g_infThreshold = *(float *)0x00e44598; // NaN/inf threshold
    static unsigned int g_exponentMask = *(unsigned int *)0x00e44680; // 0x7F800000

    // Unused local initializations (compiler artifacts)
    /* float local_44 = 0, local_34 = 0, local_24 = 0; */
    /* float local_14 = g_floatUnused0; */

    if (direction == nullptr) {
        direction = g_defaultDirection;
    }

    float dirX = direction[0];
    float dirY = direction[1];
    float dirZ = direction[2];

    // Dot product (point · direction) * scale
    float dot = dirX * point[0] + dirY * point[1] + dirZ * point[2];
    float t = dot * g_scaleFactor;

    // Project point onto the ray/line: point + t * direction
    float projX = dirX * t + point[0];
    float projY = dirY * t + point[1];
    float projZ = dirZ * t + point[2];

    // Check for infinity/NaN via exponent bit mask
    if ( (g_infThreshold < (float)((unsigned int)projX & g_exponentMask)) ||
         (g_infThreshold < (float)((unsigned int)projY & g_exponentMask)) ||
         (g_infThreshold < (float)((unsigned int)projZ & g_exponentMask)) ) {
        // Compute cross product: direction × projected
        float crossX = dirY * projZ - dirZ * projY;
        float crossY = dirZ * projX - dirX * projZ;
        float crossZ = dirX * projY - dirY * projX;

        // Unused second cross product (compiler artifact from inlined code)
        // float cross2X = crossZ * projY - crossY * projZ;
        // float cross2Y = crossX * projZ - crossZ * projX;
        // float cross2Z = crossY * projX - crossX * projY;

        // Normalize the cross product vector (FUN_0043a2a0)
        normalizeVector(&crossX, &crossX);

        // Call virtual method at vtable+0x20 (e.g., applyCorrectionForce)
        (this->*(this->vtable[0x20]))(&crossX);
    }
}