// FUNC_NAME: Animation::blendBoneTransform
// Address: 0x00511540
// This function blends a bone transform (quaternion or matrix) for a given bone index.
// It supports two blending modes: a full slerp-like blend using sin/cos (when flag 0x4000 is not set)
// and a simple lerp (when flag is set). It also handles additive animation if param_4 is non-zero.

#include <cmath>

// External globals (likely from data section)
extern float DAT_00e2b1a4; // Probably 1.0f
extern float DAT_00e44564; // Probably 1.0f
extern float _DAT_00e2e084; // Blend factor for lerp mode

// Forward declarations of called functions (names guessed based on context)
void FUN_00414aa0(); // Possibly returns a constant (e.g., 1.0f)
void FUN_0050a940(int* boneArrayBase); // Prepare bone array
void FUN_0056b8a0(float a, float b, float c); // Convert quaternion to matrix? (takes 3 floats)
void FUN_0056b420(int sourceTransform, float* outQuat, int destTransform); // Blend quaternion
void FUN_0050fe90(int* param, float angle); // Apply lerp to bone
void FUN_004eb6a0(float* transform, uint flags); // Apply additive animation
void FUN_0056b230(float* buffer); // Reset additive transform

// The function uses a custom calling convention: this in ECX, boneIndex in EAX,
// boneArrayBase on stack (param_2), sourceTransform on stack (param_3),
// destTransform in EDI (unaff_EDI), flag on stack (param_4).
void __thiscall Animation::blendBoneTransform(
    int this,               // param_1: this pointer
    int boneIndex,          // in_EAX: bone index
    int* boneArrayBase,     // param_2: base pointer to bone transform array (size 0x50 per bone)
    int sourceTransform,    // param_3: pointer to source transform (blend target)
    int destTransform,      // unaff_EDI: pointer to destination transform (output)
    int flag                // param_4: flag for additive animation
)
{
    // Thread-local storage offset (common in EA engine)
    int* tlsBase = *(int**)(__readfsdword(0x2c));
    int* boneArray = (int*)(boneIndex * 0x50 + *boneArrayBase + *(int*)(tlsBase + 8));

    // Get identity quaternion constant (probably 1.0f)
    FUN_00414aa0();
    float identityW = DAT_00e2b1a4;
    FUN_00414aa0();

    // Prepare bone array (maybe lock or update)
    FUN_0050a940(boneArrayBase);

    // Get pointer to some object from this+0x24
    int* objPtr = *(int**)(this + 0x24); // +0x24: pointer to another object (e.g., AnimationState)
    int obj = *objPtr;

    // Check if the object has a specific flag (0x4000) at offset 0x108
    if ((*(uint*)(obj + 0x108) & 0x4000) == 0)
    {
        // Complex blend using sin/cos (slerp-like)
        char blendIndex = *(char*)(obj + 0x157); // +0x157: blend index (0-3)
        uint idx1 = (0x21 >> (blendIndex * 4)) & 0xf;
        uint idx2 = (0x21 >> (idx1 * 4)) & 0xf;

        // Check if additive flag is set at obj+0x104
        if ((*(byte*)(obj + 0x104) & 2) == 0)
        {
            // Direct set: set quaternion from input angle
            float quat[4];
            quat[blendIndex] = angle; // angle is passed in XMM0? Actually in_XMM0_Da is the angle
            quat[idx1] = 0.0f;
            quat[idx2] = 0.0f;
            FUN_0056b8a0(quat[1], quat[0], quat[2]); // Convert to matrix?
        }
        else
        {
            // Blend between two transforms using sin/cos of the angle
            double angleDouble = (double)angle; // angle from XMM0
            double sinAngle = sin(angleDouble); // FUN_00b99fcb is sin
            double cosAngle = cos(angleDouble); // FUN_00b99e20 is cos
            float sinF = (float)sinAngle;
            float cosF = (float)cosAngle;

            // Copy source transform for blendIndex to destTransform (using index * 0x10)
            int srcOffset = blendIndex * 0x10;
            int* srcPtr = (int*)(srcOffset + sourceTransform);
            int* dstPtr = (int*)(srcOffset + destTransform);
            dstPtr[0] = srcPtr[0];
            dstPtr[1] = srcPtr[1];
            dstPtr[2] = srcPtr[2];
            dstPtr[3] = srcPtr[3];

            // Blend for idx2: scale by sin
            int idx2Offset = idx2 * 0x10;
            float* src2 = (float*)(idx2Offset + sourceTransform);
            float s0 = src2[0], s1 = src2[1], s2 = src2[2], s3 = src2[3];
            float* dst2 = (float*)(idx2Offset + destTransform);
            dst2[0] = sinF * s0;
            dst2[1] = sinF * s1;
            dst2[2] = sinF * s2;
            dst2[3] = sinF * s3;

            // Blend for idx1: scale by cos and add sin*original (from idx2 source)
            int idx1Offset = idx1 * 0x10;
            float* src1 = (float*)(idx1Offset + sourceTransform);
            float t0 = src1[0], t1 = src1[1], t2 = src1[2], t3 = src1[3];
            float* dst1 = (float*)(idx1Offset + destTransform);
            dst1[0] = cosF * t0 + sinF * s0;
            dst1[1] = cosF * t1 + sinF * s1;
            dst1[2] = cosF * t2 + sinF * s2;
            dst1[3] = cosF * t3 + sinF * s3;

            // Now blend for idx2 again: scale by cos and add (1-sin)*original (from idx1 source)
            float oneMinusSin = DAT_00e44564 - sinF; // DAT_00e44564 is likely 1.0f
            float* dst2b = (float*)(idx2Offset + destTransform);
            dst2b[0] = cosF * s0;
            dst2b[1] = cosF * s1;
            dst2b[2] = cosF * s2;
            dst2b[3] = cosF * s3;

            // Add (1-sin)*t to idx2
            dst2b[0] = oneMinusSin * t0 + cosF * s0;
            dst2b[1] = oneMinusSin * t1 + cosF * s1;
            dst2b[2] = oneMinusSin * t2 + cosF * s2;
            dst2b[3] = oneMinusSin * t3 + cosF * s3;
        }
    }
    else
    {
        // Simple lerp mode: interpolate bone position (offset 0x30,0x34,0x38) using global blend factor
        float* bonePos = (float*)(boneArray + 0x30); // +0x30: position X
        float* localPos = (float*)local_70; // local_70 is a float array (probably position)
        localPos[0] = (bonePos[0] - localPos[0]) * _DAT_00e2e084 + localPos[0];
        localPos[1] = (bonePos[1] - localPos[1]) * _DAT_00e2e084 + localPos[1];
        localPos[2] = (bonePos[2] - localPos[2]) * _DAT_00e2e084 + localPos[2];
        FUN_0050fe90(objPtr, angle); // Apply lerp to bone
    }

    // Check if this+0x5b == 4 and a flag in another object is set
    if ((*(char*)(this + 0x5b) == 4) &&
        ((*(byte*)(*(int*)(this + 0x10) + *(int*)(tlsBase + 8)) & 4) != 0))
    {
        // Blend quaternion from sourceTransform into destTransform+0x30
        float outQuat[4];
        FUN_0056b420(sourceTransform, outQuat, destTransform + 0x30);
        // The result is stored via extraout_EDX? Actually the code uses puVar16 = extraout_EDX
        // but then later it writes to destTransform+0x30 anyway. We'll assume the function modifies destTransform.
    }
    else
    {
        // Copy local quaternion (local_60) to destTransform+0x30
        float* destPos = (float*)(destTransform + 0x30);
        destPos[0] = local_60; // local_60 is a quaternion (4 floats)
        destPos[1] = uStack_5c;
        destPos[2] = uStack_58;
        destPos[3] = uStack_54;
    }

    // If flag is non-zero and the object has specific flags (0x180000) at offset 0x10c
    if ((flag != 0) && ((*(uint*)(obj + 0x10c) & 0x180000) != 0))
    {
        // Apply additive animation
        uint additiveFlags = (*(uint*)(obj + 0x10c) >> 0x14) & 0xffffff01;
        FUN_004eb6a0((float*)(destTransform + 0x30), additiveFlags);
        float buffer[19]; // local_50 size 76 bytes = 19 floats
        FUN_0056b230(buffer);
        // Zero out some fields in destTransform
        *(int*)(destTransform + 0xc) = 0;
        *(int*)(destTransform + 0x1c) = 0;
        *(int*)(destTransform + 0x2c) = 0;
    }
}