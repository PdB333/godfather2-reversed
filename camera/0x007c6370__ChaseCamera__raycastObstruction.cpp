// FUNC_NAME: ChaseCamera::raycastObstruction
// Function address: 0x007c6370
// Performs a raycast to detect obstacles between camera and target, adjusts camera position and sets a flag if hit is in front.
// Offsets: this+0x8e3 (byte flag, likely enable/disable), this+0x1f88 (unknown), this+0x1f8c (unknown)
// Output structure *param_3: +0x0 (float3 start), +0xC (float3 hit), +0x18 (float distance), +0x1C (byte isHitFront)

uint __thiscall ChaseCamera::raycastObstruction(void* this, uint targetId, HitResult* outResult)
{
    uint result;
    int allocPtr;
    float rayStart[3]; // local_18, local_14, local_10
    float rayEnd[3];   // local_24, fStack_20, local_1c
    float distance;
    float local_c;
    float local_4;
    void* transformPtr;
    void* transformPtr2;
    void* transformPtr3;

    result = in_EAX & 0xffffff00; // Preserve high bits from register

    // Check if this feature is enabled (flag at +0x8e3)
    if ((*(byte*)((int)this + 0x8e3) & 1) != 0) {
        return result; // Early out if disabled
    }

    // Allocate temporary memory for raycast (7,8 style)
    allocPtr = FUN_00896b30(7, 8, *(undefined4*)((int)this + 0x1f88), *(undefined4*)((int)this + 0x1f8c), 2, 0);
    if (allocPtr == 0) {
        return 0; // Allocation failed
    }

    // Get the starting position of the ray (likely camera position)
    FUN_008970a0(rayStart); // Initialize rayStart vector

    // Perform the raycast (FUN_007e94f0) - returns whether a hit was found
    result = FUN_007e94f0(targetId, rayStart, allocPtr + 8, (undefined8*)(allocPtr + 0x18), 0x10000, 8, rayEnd);
    if ((result & 0xFF) != 0) { // Check low byte for success
        return result & 0xffffff00; // Return success indicator
    }

    // Fill output structure with hit results
    outResult->start.x = rayEnd[0];      // local_24
    outResult->start.y = rayEnd[1];      // fStack_20
    outResult->start.z = rayEnd[2];      // local_1c
    outResult->hit.x = *(float*)(allocPtr + 0x18);
    outResult->hit.y = *(float*)(allocPtr + 0x1C);
    outResult->hit.z = *(float*)(allocPtr + 0x20);

    // Compute distance from start to hit point
    outResult->distance = sqrtf(
        (rayStart[0] - rayEnd[0]) * (rayStart[0] - rayEnd[0]) +
        (rayStart[1] - rayEnd[1]) * (rayStart[1] - rayEnd[1]) +
        (rayStart[2] - rayEnd[2]) * (rayStart[2] - rayEnd[2])
    );

    // Use global threshold (DAT_00e44564) to compute some offset
    local_c = DAT_00e44564 - outResult->hit.z; // +0x14 in outResult
    local_4 = outResult->hit.x; // +0x0C

    // Get three transform components (likely camera forward/up/right)
    transformPtr = (void*)FUN_00471610();
    transformPtr2 = (void*)FUN_00471610();
    transformPtr3 = (void*)FUN_00471610();

    // Check if the hit point is in front of the camera (dot product with forward direction)
    if (0.0f < *(float*)((int)transformPtr + 0x20) * local_c + 
                *(float*)((int)transformPtr2 + 0x24) * 0.0f + 
                *(float*)((int)transformPtr3 + 0x28) * local_4) {
        outResult->isHitFront = 1; // +0x1C
        return (uint)(((undefined3)((uint)((int)transformPtr3 + 0x20) >> 8)) << 8) | 1; // Pack flag
    }

    outResult->isHitFront = 0; // +0x1C
    return (uint)(((undefined3)((uint)((int)transformPtr3 + 0x20) >> 8)) << 8) | 1;
}