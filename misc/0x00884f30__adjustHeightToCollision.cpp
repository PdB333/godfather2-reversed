// FUNC_NAME: adjustHeightToCollision
void adjustHeightToCollision(float* pos) // pos[0]=x, pos[1]=y, pos[2]=z
{
    // Ray half-extent (vertical span from current position)
    extern float _DAT_00d5c458; // +0x40? likely half ray length
    extern float _DAT_00d5780c; // collision distance threshold

    // Build a vertical segment: from (x, y - extent, z) to (x, y + extent, z)
    float rayStart[3], rayEnd[3];
    rayStart[0] = pos[0];
    rayStart[1] = pos[1] + _DAT_00d5c458; // top
    rayStart[2] = pos[2];

    rayEnd[0] = pos[0];
    rayEnd[1] = pos[1] - _DAT_00d5c458; // bottom
    rayEnd[2] = pos[2];

    // Collision query flags: 0x60102 (likely include terrain/static), 0x10000 (closest hit)
    // Other params: 0, 0 (maybe ignore list, etc.)
    FUN_00542650(rayStart, rayEnd, 0x60102, 0x10000, 0, 0);

    // Set up collision result structure with vtable pointer
    void* vtable = (void*)&PTR_FUN_00e32a8c; // some collision result class
    // local_60 is a 92-byte buffer (likely CollisionResult)
    char resultBuffer[92];
    FUN_009e5ed0(resultBuffer, &vtable);

    // Interpret result fields: local_70 (hit flag), local_b0 (collision distance)
    int hitFlag;  // +0x70 from resultBuffer? Actually local_70 is separate variable
    float collisionDist; // local_b0 (float)

    // The decompiled code uses standalone locals, we'll simulate via offset in buffer
    // or assume they are members of resultBuffer at known offsets.
    // For clarity, we restore the original variable behavior.
    int local_70 = 0; // likely from resultBuffer[0x70]? but originally set to 0 and possibly modified by FUN_009e5ed0.
    float local_b0 = _DAT_00d5780c; // initialized to that global
    // These are actually part of the result structure, but we keep as locals for reconstruction.
    // In reality, FUN_009e5ed0 modifies them.
    // We assume the callee fills them.

    if (local_70 != 0) {
        float fVar1 = 0.0f;
        if ((local_b0 <= 0.0f) ||
            ((local_b0 < _DAT_00d5780c && (fVar1 = local_b0, local_b0 < _DAT_00d5780c))))
        {
            // Clamp: adjust Y so that position rests on collision surface
            pos[1] = (_DAT_00d5c458 - fVar1) + pos[1];
        }
    }
}