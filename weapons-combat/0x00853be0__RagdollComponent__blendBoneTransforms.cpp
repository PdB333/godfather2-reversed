// FUNC_NAME: RagdollComponent::blendBoneTransforms
// Address: 0x00853be0
// This function blends two bone transforms (source and destination) with a blend weight and scale factor.
// It handles ragdoll vs. animated state through a global ragdoll component instance.

#include <cstdint>

// Forward declarations
bool QueryEngineData(uint32_t hash, float* out);   // virtual at +0x10
bool IsRagdollActive(void* obj);                   // virtual at +0x238
long double GetRagdollTimeFactor(void* obj);       // virtual at +0x23c, returns a 10-byte float
void MultiplyQuaternion(float* a, float* b, float* result); // FUN_0054ba20
void LerpTransforms(float* result, float* src, float blendWeight); // FUN_0084f820

// Global pointers set by caller (EBX, ESI)
extern float* g_pTimeManager;    // FUN_00471610 returns pointer to a struct
extern void* g_pRagdollComponent; // unaff_ESI, possibly a RagdollComponent*
extern uint32_t g_someFlag;      // unaff_EBX

void __thiscall RagdollComponent::blendBoneTransforms(
    int* this_ptr,
    float* srcTransform,     // 4 floats
    float blendWeight,
    float* dstTransform,     // 4 floats
    float scale
)
{
    float localRes[4];   // fStack_28,24,20,1c
    float temp0, temp1, temp2, temp3;
    double tempTime;
    float f1, f2, f3, f4;

    // Query engine data by hash (0x55859efa -> possibly "ragdoll_controller")
    bool hasRagdollData = (**(code**)(*this_ptr + 0x10))(0x55859efa, &temp0);
    if (!hasRagdollData || g_pRagdollComponent == nullptr ||
        (!(**(code**)(*(int*)g_pRagdollComponent + 0x238))() && 
         ((*(uint32_t*)((int*)g_pRagdollComponent + 0x238) >> 0x19) & 1) == 0))
    {
        // Simple path: just scale the source transform
        localRes[0] = srcTransform[0] * scale;
        localRes[1] = srcTransform[1] * scale;
        localRes[2] = srcTransform[2] * scale;
        localRes[3] = srcTransform[3] * scale;
    }
    else
    {
        // Ragdoll active: more complex blending
        long double ragdollTimeFactor = (**(long double (**)())(*(int*)g_pRagdollComponent + 0x23c))();
        float ragdollDuration = *(float*)((int*)g_pRagdollComponent + 0x23e); // offset 0x8F8
        blendWeight = (float)(ragdollTimeFactor * (long double)blendWeight);

        // Get time manager data
        void* timeMgr = (void*)FUN_00471610(); // returns pointer to a struct
        uint64_t timeStamp = *(uint64_t*)((char*)timeMgr + 0x30);
        float frameTime = *(float*)((char*)timeMgr + 0x38);

        // Compute differences relative to ragdoll's internal data
        uint64_t ragdollData = *(uint64_t*)((int*)g_pRagdollComponent + 0x23c); // offset 0x8F0
        float ragdollFloat = *(float*)((int*)g_pRagdollComponent + 0x23e); // offset 0x8F8

        float diff0 = (float)ragdollData - (float)timeStamp;
        float diff1 = *(uint32_t*)((uint64_t*)&ragdollData + 1) - (float)(timeStamp >> 32);
        float diff2 = ragdollFloat - frameTime;

        // Call quaternion multiplication (or similar)
        float mulResult[4];
        MultiplyQuaternion(&diff0, &f2, mulResult); // actual arguments may differ

        if (scale <= 0.0f)
        {
            // Linear interpolation when scale <= 0
            localRes[0] = mulResult[0] * scale + (float)timeStamp;
            localRes[1] = mulResult[1] * scale + (float)(timeStamp >> 32);
            localRes[2] = mulResult[2] * scale + frameTime;
        }
        else
        {
            localRes[0] = mulResult[0];
            localRes[1] = mulResult[1];
            localRes[2] = mulResult[2];
        }
        // Fourth component uses a global constant
        localRes[3] = _DAT_00d5780c - dstTransform[3];
    }

    // Final blending of the computed result with source transform
    LerpTransforms(localRes, srcTransform, blendWeight);
    return;
}