// FUNC_NAME: Skeleton::updateBoneTransforms

#include <cmath>

// External constants from the game's data section
static const float kHalfSinConstant = 0.5f; // DAT_00e2cd54
static const float kOne = 1.0f;             // DAT_00e2b1a4
static const float kTransformScale = 1.0f;  // DAT_00e2b04c
static const float kTranslationOffset = 0.0f; // DAT_00e2b05c

// Forward declaration of external functions
float MathSqrt(float value); // FUN_00414a80 - square root
void TransformVectorByMatrix(float* matrix, float* inVec, float* outVec); // FUN_00aa2cd0

// Structure representing a bone's local transform (input)
struct BoneLocalData {
    float offset0[4];   // +0x00: unknown
    float quatPart[4];  // +0x10: quaternion (axis/angle representation)
};

// Structure representing output per bone
struct BoneOutput {
    float worldPos[4];      // +0x70: world position (quaternion? Actually matrix row0)
    float axis[4];          // +0x90: normalized rotation axis (x,y,z,w?) 
    float invLength;        // +0x9c: reciprocal of vector length
};

// Skeleton class layout (inferred)
struct Skeleton {
    int8_t boneCount;       // +0x20
    // +0x18: pointer to world matrices array
    // +0x1c: pointer to bone hierarchy (contains local rotations and bone data)
    // +0x34: pointer to an array of BoneLocalData
    // +0x48: pointer to array of BoneOutput (one per bone)
    // +0xc0: pointer to float array (blend weights)
};

// Main function: compute blended world-space bone transforms
void Skeleton::updateBoneTransforms()
{
    float* worldMatrices = *(float**)(this + 0x18);      // array of 4x4 matrices, each 16 floats
    int8_t* boneInfo = *(int8_t**)(this + 0x1c);        // structure with bone data
    BoneLocalData* localBoneData = *(BoneLocalData**)(*(int*)(this + 0x34) + 8); // base of local quaternions
    BoneOutput* outputBones = *(BoneOutput**)(this + 0x48);
    float* blendWeights = *(float**)(this + 0xc0);      // per-bone blend factor

    int boneIndex = 0;
    int localOffset = 0;   // offset into localBoneData array (0x30 per bone)
    int outputOffset = 0;  // offset into outputBones array (0xc0 per bone)

    // Bone count is stored as a signed char in the hierarchy structure
    int8_t boneCount = boneInfo[0x20];

    if (boneCount > 0) {
        do {
            // Read the axis/angle vector from local bone data
            // The vector is stored at offset 0x10 within BoneLocalData
            float* localQuat = (float*)((uint8_t*)&localBoneData[boneIndex] + 0x10);
            float axisX = localQuat[0];
            float axisY = localQuat[1];
            float axisZ = localQuat[2];

            // Scale the axis by the blend weight and a fixed constant
            float scaleFactor = blendWeights[boneIndex] * kHalfSinConstant;
            float scaledX = axisX * scaleFactor;
            float scaledY = axisY * scaleFactor;
            float scaledZ = axisZ * scaleFactor;

            // Compute length squared of scaled axis, plus constant (likely +1.0 to form w^2)
            float sumSq = scaledX*scaledX + scaledY*scaledY + scaledZ*scaledZ + kOne;

            float invLength = 0.0f;
            if (sumSq != 0.0f) {
                invLength = 1.0f / MathSqrt(sumSq);
            }

            // Store the normalized rotation axis and the reciprocal length
            outputBones[boneIndex].axis[0] = invLength * scaledX;
            outputBones[boneIndex].axis[1] = invLength * scaledY;
            outputBones[boneIndex].axis[2] = invLength * scaledZ;
            outputBones[boneIndex].invLength = invLength;

            // Copy the parent bone's world rotation (a 4-float component) into the output
            // This comes from boneInfo at offset 0x50 (likely a quaternion or matrix row)
            float* parentRot = (float*)(boneInfo + 0x50);
            float* outputRot = outputBones[boneIndex].worldPos;
            outputRot[0] = parentRot[0];
            outputRot[1] = parentRot[1];
            outputRot[2] = parentRot[2];
            outputRot[3] = parentRot[3];

            // Now compute a transformed vector using the bone's local rotation and parent data
            // This is a complex quaternion multiplication or cross/dot product calculation
            float w = outputBones[boneIndex].invLength;
            float wSqMinusConst = w * w - kHalfSinConstant;

            float pX = outputBones[boneIndex].worldPos[0];
            float pY = outputBones[boneIndex].worldPos[1];
            float pZ = outputBones[boneIndex].worldPos[2];
            float pW = outputBones[boneIndex].worldPos[3];

            float aX = outputBones[boneIndex].axis[0];
            float aY = outputBones[boneIndex].axis[1];
            float aZ = outputBones[boneIndex].axis[2];

            // Dot product between parent rotation and local axis
            float dot = aX * pX + aY * pY + aZ * pZ;

            // Cross product components (parent rotation x local axis)
            float crossX = pY * aZ - pZ * aY;
            float crossY = pZ * aX - pX * aZ;
            float crossZ = pX * aY - pY * aX;

            // Final vector to be transformed by the world matrix
            float resultVec[4];
            resultVec[0] = (crossX * w + aX * dot + pX * wSqMinusConst) * kTransformScale;
            resultVec[1] = (crossY * w + aY * dot + pY * wSqMinusConst) * kTransformScale;
            resultVec[2] = (crossZ * w + aZ * dot + pZ * wSqMinusConst) * kTransformScale;
            resultVec[3] = (w * kTranslationOffset + dot * w + pW * wSqMinusConst) * kTransformScale;

            // Apply the world matrix to this vector and store back into the world matrix array
            TransformVectorByMatrix(&worldMatrices[boneIndex * 16 + 0xe0], resultVec, resultVec);
            // The call likely modifies the matrix at that location or stores the result

            boneIndex++;
            localOffset += 0x30;
            outputOffset += 0xc0;
        } while (boneIndex < boneCount);
    }
}