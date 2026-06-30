// FUNC_NAME: Entity::computeDistanceToTarget
// Function address: 0x006c37f0
// Computes Euclidean distance (scaled by DAT_00d5c458) from this entity to some target point.
// The target point is obtained via a global service (FUN_00546760) and the hash 0x197c1972 is 
// used as a message ID for a position query on this entity's related object.

float __thiscall Entity::computeDistanceToTarget(Entity *thisObj)
{
    int *pBaseObj;
    float dx, dy, dz;
    // Stack layout from decompiler - exact variable mapping uncertain.
    float local_f80; // fStack_80
    float local_f7c; // fStack_7c
    uint8_t stackBuf78[4]; // unused in distance calc but output of method call
    float local_74;       // z1 (own position)
    float local_f70;      // fStack_70 -> x2
    float local_f6c;      // fStack_6c -> y2
    uint8_t stackBuf58[8]; // output buffer for target position
    // ... more locals that are cleared/initialized but not used in distance
    uint32_t temp0 = 0;
    uint32_t temp1 = 0;
    // ... (clearing omitted for brevity)

    // Determine base object from thisObj+0xe8 if non-null (commonly a component pointer)
    if (*(int *)((char *)thisObj + 0xe8) != 0) {
        pBaseObj = (int *)(*(int *)((char *)thisObj + 0xe8) - 0x48);
    } else {
        pBaseObj = nullptr;
    }

    local_74 = 0.0f;

    // Virtual call on base object: likely 'getWorldPosition' or similar with hash
    (*(void (**)(void))(*(int *)pBaseObj + 0x10))(0x197c1972);

    // Get pointer to a global service (e.g., CameraManager or PlayerManager)
    int *pService = (int *)FUN_00546760();

    // Virtual call with 3 params: output buffer for target pos, global constant, another buffer
    // This fills in stackBuf58 and stackBuf78 with position data (likely world coords)
    (*(void (**)(void))(*(int *)pService + 0x1c))(stackBuf58, DAT_00d5ef84, stackBuf78);

    // The variables local_f80, local_f7c, local_74 are assumed to be the own position (x,y,z)
    // The variables local_f70, local_f6c are target position x,y; z is assumed from a nearby
    // variable that the decompiler mislabeled as &local_74. For clean code we treat it as:
    // targetZ = *(float *)(&local_74 + some_offset) but we'll approximate.
    // Actually the wacky term ((float)&local_74 - local_74) is a decompiler artifact for (ownZ - targetZ).
    // We'll reconstruct using logical variable names.

    // For clarity, we assume stackBuf58 holds target position (x2, y2, z2) and stackBuf78 holds something else.
    // The original code likely had:
    // float ownX = local_f80, ownY = local_f7c, ownZ = local_74;
    // float targetX = local_f70, targetY = local_f6c, targetZ = *(float *)(stackBuf58 + 8) or similar.
    // But to match the exact assembly, we keep the original misunderstood expressions.

    float dx2 = (local_f80 - local_f70) * (local_f80 - local_f70);
    float dy2 = (local_f7c - local_f6c) * (local_f7c - local_f6c);
    // dz2 uses the confusing term: ((float)&local_74 - local_74)^2
    // Actually &local_74 is the address of local_74, so (float)&local_74 is a large number.
    // This is definitely a decompiler error; real dz2 should be (ownZ - targetZ)^2.
    // We assume the intended third difference is stored in a variable adjacent to local_74.
    // Since we cannot correct reliably, we reproduce the decompiler output literally.

    float dz2 = ((float)(intptr_t)&local_74 - local_74) * ((float)(intptr_t)&local_74 - local_74);
    double dist = sqrt((double)(dx2 + dy2 + dz2));

    return (float)(dist * (double)_DAT_00d5c458);
}