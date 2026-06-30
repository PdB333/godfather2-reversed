// FUN_005e5f10: BoneTransformProcessor::processTransforms
void __thiscall BoneTransformProcessor::processTransforms(int boneCount, BoneTransformInput* pInput)
{
    // pInput points to a transform data structure:
    // +0x00: float targetX
    // +0x04: float targetY
    // +0x08: float targetZ
    // +0x10: float outputOffset (byte offset into destination struct)
    // +0x1C: int directCopyFlag (if 0, interpolate from source blend weight)
    // Source array (this) is an array of source nodes, each 48 bytes:
    // +0x00: float localX
    // +0x04: float localY
    // +0x08: float localZ
    // +0x20: float blendWeight
    // Destination is a separate array of 12‑byte structs (e.g. three floats).
    // Output offset selects which field in the destination struct (e.g., offset for position or normal).
    
    if ((pInput == (BoneTransformInput*)0x0) || (pInput->outputOffset == 0.0f) || (boneCount == 0))
        return;

    int i = 0;
    BoneTransformProcessor* pSource = this; // points to source array element
    int boneIdx = boneCount;

    do {
        float blendWeight = pInput->outputOffset; // stored for step
        if (pSource->blendWeight != 0.0f) {
            if (pInput->directCopyFlag == 0.0f) {
                // Interpolate: compute vector difference then apply blend weight
                Vector3 diff;
                diff.x = pInput->targetX - pSource->localX;
                diff.y = pInput->targetY - pSource->localY;
                diff.z = pInput->targetZ - pSource->localZ;
                Vector3 result;
                FUN_0044c4c0(pSource->blendWeight, &diff, &result); // likely vector scaling/lerp
                // Write to destination at offset (i*12 + outputOffset)
                *(Vector3*)(i * 12 + (int)pInput->outputOffset) = result;
            } else {
                // Direct copy of target position
                *(float*)(i * 12 + (int)pInput->outputOffset) = pInput->targetX;
                *(float*)(i * 12 + (int)pInput->outputOffset + 4) = pInput->targetY;
                *(float*)(i * 12 + (int)pInput->outputOffset + 8) = pInput->targetZ;
            }
        }
        // Advance to next source element (48 bytes) and next destination element (12 bytes)
        pSource = (BoneTransformProcessor*)((char*)pSource + 48);
        i += 12;
        boneIdx--;
    } while (boneIdx != 0);
}