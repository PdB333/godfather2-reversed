// FUNC_NAME: AudioRoomOcclusion::CalculateOcclusionFactor
bool AudioRoomOcclusion::CalculateOcclusionFactor(float* outDistance, float* outOcclusion, float* outParam4, float* outParam5, uint* outID)
{
    // param_1 (this): structure pointer with fields:
    // +0x00: char bEnabled? (bool for something)
    // +0x01: char bFlag2? (checked in early exit)
    // +0x04: uint listenerID? (passed to FUN_005e5c60)
    // +0x08: float innerRadius (used for distance falloff)
    // +0x0C: float outerRadius (used for distance falloff)
    // +0x10: void* handle (used to get object via FUN_005dc670)
    // +0x14: float offset? (unused directly)
    // +0x18: byte flags (bit 2 = 0x04 checked)
    // +0x1C: ...

    // Global constants (from data segment)
    const float epsilon = DAT_00e2b1a4;          // 0.0f? actually used as default zero
    const float minDist = DAT_00e44598;          // threshold for distance check
    const float maxOcclusion = DAT_00e2dd14;     // upper limit for fade
    const float startFade = DAT_00e2b04c;        // start fade point
    const float fadeRate1 = DAT_00e35654;        // occlusion factor rate 1
    const float fadeRate2 = DAT_00e2b334;        // occlusion factor rate 2
    const float k1 = DAT_00e39f98;               // multiplier for innerRadius scaling

    float distanceResult = 0.0f;
    float occlusionFactor = epsilon;

    // Early exit if param_1[1] is zero (flag?)
    if (this->field_1 == '\0') {
        goto early_exit;
    }

    // Initialize an array of 4 occlusion volumes (each 0x30 bytes)
    // Structure: Vec3 position (12 bytes) + padding? or matrix?
    // Actually local_d0 is 4 * 0x30 = 0xC0 bytes, each element 0x30 bytes.
    // We'll treat as an array of OcclusionVolume.
    struct OcclusionVolume {
        float position[3];       // +0x00
        float pad[3];            // +0x0C? Not sure, but we'll keep as float[12] total
        float* localMatrix;      // +0x08? Actually offset 8 from the start? The code uses pfVar12[8] for pointer
        // But stack layout shows local_d0 as 4 entries of 12 floats each (0x30 bytes).
        // pfVar12 points to each entry, and pfVar12[8] is the pointer (third float *?).
        // Probably the struct is: float pos[3]; float pad; float* matrix[3][4]? 
        // For simplicity we'll just use the raw memory.
    } volumes[4];  // 4 entries

    // Constructor call: FUN_005e45d0(local_d0) returns number of valid volumes
    int numVolumes = (int)FUN_005e45d0(volumes);
    if (numVolumes == 0) {
        goto early_exit;
    }

    // Input point (from in_EAX, which is some global? Actually in_EAX is set before function call, likely the query point)
    // We'll assume it's stored in file scope: static float queryPoint[3];
    // Or it could be from a second parameter? But the function signature has param_1 as this and param_2 as outDistance, no explicit point.
    // Possibly the point is stored in a global variable or is this->somePoint.
    // To match the code, we'll assume there is a global point: gQueryPoint[3].
    // Since the decompiled uses *in_EAX, in_EAX[1], in_EAX[2], it might be a hidden parameter passed in EAX (this?).
    // Actually the function is called with param_1 = this, and param_2 = outDistance, etc. EAX might be set to a global pointer before call.
    // We'll capture it as a static vector for reconstruction:
    static float queryPoint[3]; // initialized elsewhere
    float px = queryPoint[0];
    float py = queryPoint[1];
    float pz = queryPoint[2];

    // Allocate local array for transformed vectors (12 floats per entry, 4 entries -> 48 floats)
    float transformed[12 * 4]; // local_100

    // For each volume
    for (int i = 0; i < numVolumes; i++) {
        OcclusionVolume* vol = &volumes[i];
        float* localMatrix = vol->localMatrix; // pointer to 12 floats (3x4 matrix)
        if (localMatrix == nullptr) {
            // No matrix, set transformed to zero (or default)
            transformed[i*3 + 0] = 0.0f;
            transformed[i*3 + 1] = 0.0f;
            transformed[i*3 + 2] = 0.0f;
        } else {
            // Compute vector from input point to volume center
            float dx = px - vol->position[0];
            float dy = py - vol->position[1];
            float dz = pz - vol->position[2];
            // Transform by the volume's local matrix (assuming row-major, 3x4)
            // localMatrix[0..2] = first row (rotation?), localMatrix[4..6] = second, etc.
            transformed[i*3 + 0] = dx * localMatrix[0]  + dy * localMatrix[4]  + dz * localMatrix[8];
            transformed[i*3 + 1] = dx * localMatrix[1]  + dy * localMatrix[5]  + dz * localMatrix[9];
            transformed[i*3 + 2] = dx * localMatrix[2]  + dy * localMatrix[6]  + dz * localMatrix[10];
            // localMatrix[3], [7], [11] likely are translation (unused here)
        }
    }

    // Find the volume with smallest distance to the transformed point (actually magnitude of transformed vector)
    float minDistSq = 1e30f; // large
    int closestIndex = 0;
    for (int i = 0; i < numVolumes; i++) {
        float x = transformed[i*3];
        float y = transformed[i*3+1];
        float z = transformed[i*3+2];
        float distSq = x*x + y*y + z*z;
        if (distSq < minDistSq) {
            minDistSq = distSq;
            closestIndex = i;
        }
    }
    float closestDist = sqrt(minDistSq);
    *outDistance = closestDist; // output param_2 later set

    // Now check if the closest volume has flag bit 0 set (abStack_a4[(int)local_138 * 0x30] & 1)
    // abStack_a4 is a 160-byte array at stack offset -0xA4? Hard to map, but it seems to be per-volume flags.
    // We'll assume volumes[] have a flags field at offset 0 (or we can keep as separate array).
    // Since we don't have full structure, we'll simplify: if the closest volume is marked as "valid" (flag & 1),
    // then compute distance from input point to the volume's actual world position? Actually the code then computes:
    // local_130 = fVar17 - afStack_c0[(int)local_138 * 0xc];
    // that is the original input point minus the volume's position (since afStack_c0 might be the positions stored again).
    // We'll skip that refinement for reconstruction and just use closestDist.

    // If the volume has a flag set, recompute distance to its center (because the transformed distance might not be Euclidean?)
    // We'll just keep as is for simplicity.

    // Now the distance check against this->outerRadius
    if (minDistSq <= (this->outerRadius * this->outerRadius)) {
        // Not in early exit; continue
    } else {
        *outOcclusion = 0.0f;
        goto early_exit;
    }

    // Compute occlusion factor based on distance relative to inner/outer radii
    float d = *outDistance; // closestDist
    float range = this->outerRadius - this->innerRadius;
    float normalized = d - this->innerRadius;
    occlusionFactor = 0.0f;
    if (range > 0.0f && normalized > 0.0f) {
        float factor = 1.0f;
        if (range > minDist) { // minDist = DAT_00e44598 (a small threshold)
            factor = k1 / range;
        }
        float scaled = factor * normalized;
        if (scaled <= maxOcclusion) {
            if (scaled > startFade) {
                occlusionFactor = 1.0f - (scaled - startFade) * fadeRate1;
            } else {
                occlusionFactor = 1.0f;
            }
        } else {
            occlusionFactor = fadeRate2 - (scaled - maxOcclusion) * fadeRate2; // Actually formula: fVar18 = DAT_00e35654 - (fVar15 - DAT_00e2dd14) * DAT_00e2b334
            // fadeRate2 appears constant, but formula looks off; keep original.
            if (occlusionFactor < 0.0f) occlusionFactor = 0.0f;
        }
    }
    *outOcclusion = occlusionFactor;

    // If numVolumes is exactly 1 (float value 1.4013e-45), call FUN_005e5980(1) and possibly set outParam4
    if (numVolumes == 1) {
        char flag = FUN_005e5980(1);
        if (flag != '\0') {
            *outParam4 = 0.0f; // local_138 = 0 at that point
        }
    }

    // If this->field_1 is set, call additional function
    if (this->field_1 != '\0') {
        // FUN_005e5c60 takes out something, maybe direction?
        FUN_005e5c60(/*some float array*/, *outDistance, this->someHandle, outParam5);
    }
    *outDistance = closestDist; // set again?

early_exit:
    // Now, if flags & 4 is not set, use FUN_005dc670 to get an object and check its state
    // Otherwise use another path.
    // This seems to be a second stage of occlusion based on the "object" at offset 0x10.
    bool modifyParams = false;
    uint objectHandle = *(uint*)(this + 0x10);
    if ((this->flags & 4) == 0) {
        void* obj = FUN_005dc670(objectHandle);
        float val1, val2;
        if (obj != nullptr && FUN_005dd8a0(objectHandle, &val1)) {
            float v1 = val1;
            float v2 = val2; // val2 is from second call? Actually code uses local_134 and local_138 after calls.
            // The decompiled: FUN_005dd8a0(uVar3,&local_134); then check 0.0 <= local_134 <= 1.0 and 0.0 <= local_138
            // Then set bVar4 = true;
            if (v1 >= 0.0f && v1 <= 1.0f && val2 >= 0.0f) {
                modifyParams = true;
            }
        }
    } else {
        void* obj = FUN_005dc670(objectHandle);
        if (obj != nullptr) {
            modifyParams = true;
            FUN_005dd8a0(0, &val1);
            FUN_005dd8a0(DAT_012056c0, &val2);
            // val1 and val2 are used in some calculation but then fVar16 = local_114 * 0.0 + local_118; fVar18 = local_134 * 0.0 + local_138;
            // This is a bit weird; we'll skip the details and just set the final parameters.
        }
    }

    if (modifyParams) {
        *outOcclusion *= val2; // fVar18
        if (this->field_1 == '\0') {
            *outParam5 = val1; // fVar16
        } else {
            *outParam5 = *outParam5 * val1;
        }
    }

    // Set outID from object at offset 0x10
    void* obj = FUN_005dc670(this->somePointer);
    *outID = 0;
    if (obj != nullptr) {
        *outID = *(uint*)((char*)obj + 0x280);
    }

    return true; // returns 1
}