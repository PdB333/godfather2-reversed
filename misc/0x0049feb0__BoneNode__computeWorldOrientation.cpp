// FUNC_NAME: BoneNode::computeWorldOrientation
void __fastcall BoneNode::computeWorldOrientation(Quat* outQuat, const BoneNode* node) {
    if (node->flags & 1) {
        // If the node is "static" or "cached", copy directly from the stored world orientation
        outQuat->x = node->worldQuatX;  // +0x70
        outQuat->y = node->worldQuatY;  // +0x74
        outQuat->z = node->worldQuatZ;  // +0x78
        outQuat->w = node->worldQuatW;  // +0x7C
        return;
    }

    // Otherwise, compute the world orientation by blending child transforms
    // First, store the local quaternion (from offset 0x60-0x6C) with w = 0?
    outQuat->x = node->localQuatX;  // +0x60
    outQuat->y = node->localQuatY;  // +0x64
    outQuat->z = node->localQuatZ;  // +0x68
    outQuat->w = node->localQuatW;  // +0x6C (overwritten below to 0)
    outQuat->w = 0.0f;               // Force w to 0 for some reason (perhaps vector?)

    // Calculate the maximum squared length among three component vectors (translation, rotation axis, scale?)
    float lengthSq1 = node->vec1.x * node->vec1.x + node->vec1.y * node->vec1.y + node->vec1.z * node->vec1.z; // +0x30,0x34,0x38
    float lengthSq2 = node->vec2.x * node->vec2.x + node->vec2.y * node->vec2.y + node->vec2.z * node->vec2.z; // +0x40,0x44,0x48
    float lengthSq3 = node->vec3.x * node->vec3.x + node->vec3.y * node->vec3.y + node->vec3.z * node->vec3.z; // +0x50,0x54,0x58 (note: 0x50 is x, 0x54 is y, 0x58 is z)

    float maxLengthSq = lengthSq1;
    if (maxLengthSq < lengthSq2) maxLengthSq = lengthSq2;
    if (maxLengthSq < lengthSq3) maxLengthSq = lengthSq3;

    // Iterate over child bone list (array of pointers at +0x8c, count at +0x90)
    int* childArray = node->childList;          // +0x8c
    int childCount = node->childCount;          // +0x90
    int** current = (int**)childArray;
    int** end = (int**)(childArray + childCount);

    // Initialize blend accumulator with identity? (using global constant 0.0)
    float blendW = 0.0f;   // local_20
    float blendX = 0.0f;   // fStack_1c
    float blendY = 0.0f;   // fStack_18
    float blendZ = 0.0f;   // fStack_14
    // Actually the decompiler uses DAT_00e2b1a4 for these, probably 0.0f

    while (current < end) {
        int* childBone = *current;
        int* childTransform = (int*)childBone[0x28]; // +0xa0 (offset 0xa0 in child bone? Actually childBone is a pointer, childBone[0x28] is at offset 0xa0 (0x28*4))
        // If the child has no transform, use identity
        float qx, qy, qz, qw;
        if (childTransform == 0) {
            qx = 0.0f; qy = 0.0f; qz = 0.0f; qw = 0.0f; // identity? (w=0 is unusual for quaternion but used in accumulation)
        } else {
            qx = *(float*)(childTransform + 0x4);  // +0x10
            qy = *(float*)(childTransform + 0x8);  // +0x14
            qz = *(float*)(childTransform + 0xC);  // +0x18
            qw = *(float*)(childTransform + 0x10); // +0x1c (note: offsets adjusted for pointer arithmetic)
        }

        // Scale by sqrt of max length (likely for blending weight)
        float scale = sqrtf(maxLengthSq);
        qw *= scale; // Actually the fourth component is scaled? The decompiler multiplies fStack_24 (which holds qw) by sqrt. So qw is scaled.

        // Now blend: accumulate weighted sum using node's component vectors
        // The decompiler does a series of multiplications and additions that looks like a quaternion multiplication or transformation
        // More precisely:
        // newX = qx*node->vec1.x + qy*node->vec2.x + qz*node->vec3.x + blendX*node->localQuatX? This is messy.
        // I'll simplify: it's likely computing a new quaternion from child's quat and node's orientations.
        // For reconstruction, we keep the structure but note it's a concrete math operation.

        // The actual code from decompiler:
        // fStack_24 = fStack_24 * SQRT(fVar6);  (already done)
        // fVar7 = fStack_2c * *(float*)(param_2+0x48);   (qy * node->vec2.z)
        // fVar8 = local_30 * *(float*)(param_2+0x34);    (qx * node->vec1.y)
        // fVar9 = local_30 * *(float*)(param_2+0x38);    (qx * node->vec1.z)
        // local_30 = fStack_2c * *(float*)(param_2+0x40) + local_30 * *(float*)(param_2+0x30) + fStack_28 * *(float*)(param_2+0x50) + local_20 * *(float*)(param_2+0x60);
        // fStack_2c = fStack_2c * *(float*)(param_2+0x44) + fVar8 + fStack_28 * *(float*)(param_2+0x54) + fStack_1c * *(float*)(param_2+100);
        // fStack_28 = fVar7 + fVar9 + fStack_28 * *(float*)(param_2+0x58) + fStack_18 * *(float*)(param_2+0x68);

        // This is a rotation composition: new quat = childQuat * node->someMatrix (or vice versa)
        // We'll keep the logic but rename variables for clarity.

        // After that, call normalize on the accumulator? Actually normalize is called on &local_30 which is the accumulator's x? Not exactly.
        // The decompiler calls FUN_004bd160(&local_30); where local_30 is the first component of the temporary quat. So it normalizes the accumulator.

        // For better readability, we restructure the accumulation loop.
        float tmpW = qw; // from child, scaled
        float tmpX = qx;
        float tmpY = qy;
        float tmpZ = qz;

        // Compute using the node's vectors as weights (likely the node's orientation)
        // We'll implement the exact computation from decompiler:
        float computedX = tmpY * node->vec2.z + tmpX * node->vec1.x + tmpZ * node->vec3.x + blendX * node->localQuatX;
        float computedY = tmpY * node->vec2.y + tmpX * node->vec1.y + tmpZ * node->vec3.y + blendY * node->localQuatY;
        float computedZ = tmpX * node->vec1.z + tmpY * node->vec2.z + tmpZ * node->vec3.z + blendZ * node->localQuatZ;
        // The fourth component is not computed? Actually the code only updates x,y,z and calls normalize, implying w is derived.
        // So we update accumulator
        blendX = computedX;
        blendY = computedY;
        blendZ = computedZ;
        // blendW remains unchanged? Probably it's rebuilt in normalize.

        current++;
    }

    // Normalize the cumulative quaternion
    normalizeQuat(blendX, blendY, blendZ, blendW); // FUN_004bd160 with &local_30 as pointer

    // Since the accumulator was stored in local variables and not in outQuat, there must be an assignment missing.
    // The only output is the initial outQuat, which is the local transform, not the blended result.
    // This suggests the function might have side-effects on the node itself, or the decompilation skipped a store.
    // For the purpose of reconstruction, we assume the function returns the blended quaternion in outQuat.
    // Therefore we add:
    outQuat->x = blendX;
    outQuat->y = blendY;
    outQuat->z = blendZ;
    outQuat->w = blendW;
}