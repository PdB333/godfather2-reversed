// FUNC_NAME: ModelInstance::updateSkinningTransforms
// Address: 0x00560810
// This function computes skinning bone transforms for a skinned model instance.
// It iterates over bones, applies scaling, computes quaternion and translation,
// and combines them into a final transform buffer.

void ModelInstance::updateSkinningTransforms()
{
    // Constants from data section (likely 1.0, 0.0, etc.)
    const float kScaleFactor = DAT_00e2cd54; // maybe 1.0
    const float kEpsilon = DAT_00e2b1a4;     // maybe 0.0
    const float kTransformFactor = DAT_00e2b04c; // scaling for final transform
    const float kTranslationFactor = DAT_00e2b05c; // scaling for translation

    // m_pBoneTransformBuffer (this+0x18) - output array of matrices/quaternions (each stride 0xC0)
    int* boneTransformBuffer = *(int**)(this + 0x18);
    // m_pSkeletonData (this+0x1c) - skeleton definition with bone count at +0x20
    int* skeletonData = *(int**)(this + 0x1c);
    int boneCount = *(char*)(skeletonData + 0x20); // number of bones (byte)

    // m_pBoneWeights (this+0xc0) - array of per-bone scale factors
    float* boneWeights = *(float**)(this + 0xc0);

    // m_pBindPose (this+0x34) -> pointer to array of source vectors (offset +8)
    int* bindPosePtr = *(int**)(this + 0x34);
    float* sourceVectors = *(float**)(bindPosePtr + 8); // array of vec3 (stride 0x30)

    // m_pOutputBoneData (this+0x48) - base address for output bone transforms (each stride 0xC0)
    int* outputBase = *(int**)(this + 0x48);

    int boneIndex = 0;
    int outputOffset = 0; // byte offset into output buffer
    int sourceOffset = 0; // byte offset into source vectors

    if (boneCount > 0)
    {
        do
        {
            // Current output bone data
            int* outputBone = outputBase + outputOffset;

            // Scale factor for this bone (weight * constant)
            float scale = boneWeights[boneIndex] * kScaleFactor;

            // Source bone vector (position or rotation axis) from bind pose
            float srcX = sourceVectors[sourceOffset + 0x10 / 4]; // offset 0x10
            float srcY = sourceVectors[sourceOffset + 0x14 / 4]; // offset 0x14
            float srcZ = sourceVectors[sourceOffset + 0x18 / 4]; // offset 0x18

            // Compute scaled source vector
            float vecX = srcX * scale;
            float vecY = srcY * scale;
            float vecZ = srcZ * scale;

            // Compute length squared of scaled vector
            float lenSq = vecX * vecX + vecY * vecY + vecZ * vecZ + kEpsilon;

            // Compute reciprocal length (using sqrt)
            float invLen = 0.0f;
            if (lenSq != 0.0f)
            {
                invLen = 1.0f / (float)FUN_00414a80(lenSq); // sqrt or rsqrt
            }

            // Store quaternion (x,y,z,w) at output offset +0x90,0x94,0x98,0x9c
            outputBone[0x9c / 4] = invLen; // w
            outputBone[0x90 / 4] = invLen * vecX; // x
            outputBone[0x94 / 4] = invLen * vecY; // y
            outputBone[0x98 / 4] = invLen * vecZ; // z

            // Copy translation from skeleton data (offset +0x50) to output (offset +0x70)
            outputBone[0x70 / 4] = *(int*)(skeletonData + 0x50); // x
            outputBone[0x74 / 4] = *(int*)(skeletonData + 0x54); // y
            outputBone[0x78 / 4] = *(int*)(skeletonData + 0x58); // z
            outputBone[0x7c / 4] = *(int*)(skeletonData + 0x5c); // w (maybe)

            // Compute a combined transform (likely quaternion multiplication and addition)
            float w = outputBone[0x9c / 4];
            float wSq = w * w - kScaleFactor; // w^2 - 1

            // Dot product of quaternion parts with translation
            float dot = outputBone[0x90 / 4] * outputBone[0x70 / 4] +
                        outputBone[0x94 / 4] * outputBone[0x74 / 4] +
                        outputBone[0x98 / 4] * outputBone[0x78 / 4];

            // Cross product components
            float crossX = outputBone[0x78 / 4] * outputBone[0x94 / 4] -
                           outputBone[0x74 / 4] * outputBone[0x98 / 4];
            float crossY = outputBone[0x70 / 4] * outputBone[0x98 / 4] -
                           outputBone[0x90 / 4] * outputBone[0x78 / 4];
            float crossZ = outputBone[0x90 / 4] * outputBone[0x74 / 4] -
                           outputBone[0x70 / 4] * outputBone[0x94 / 4];

            // Combine into final transform vector
            float resultX = (crossX * w + outputBone[0x90 / 4] * dot + outputBone[0x70 / 4] * wSq) * kTransformFactor;
            float resultY = (crossY * w + outputBone[0x94 / 4] * dot + outputBone[0x74 / 4] * wSq) * kTransformFactor;
            float resultZ = (crossZ * w + outputBone[0x98 / 4] * dot + outputBone[0x78 / 4] * wSq) * kTransformFactor;
            float resultW = (w * kTranslationFactor + w * dot + outputBone[0x7c / 4] * wSq) * kTransformFactor;

            // Call function to add this transform to the output buffer (boneTransformBuffer + 0xe0)
            // This likely accumulates the final bone matrix
            FUN_00aa2cd0(boneTransformBuffer + 0xe0, &resultX);

            // Advance to next bone
            skeletonData = *(int**)(this + 0x1c); // reload skeleton data (might have changed?)
            outputOffset += 0xc0; // stride 0xC0
            sourceOffset += 0x30; // stride 0x30
            boneIndex++;
        }
        while (boneIndex < *(char*)(skeletonData + 0x20));
    }
    return;
}