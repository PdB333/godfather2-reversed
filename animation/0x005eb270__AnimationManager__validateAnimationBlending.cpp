// FUNC_NAME: AnimationManager::validateAnimationBlending
// Function at 0x005eb270 - Checks if animation blending is within valid joint pose ranges for a character.
// Iterates over hierarchies: animation set -> bone controllers -> keyframes, compares against target skeleton.
// Returns 0 if any keyframe is out of range, else 1.

#include <cstdint>

// Forward declarations of called functions (from engine)
extern void* getAnimationSet(uint32_t animSetId); // 0x005e9a20
extern void pushMatrixStack(); // 0x00c9eac0
extern void applyBoneTransform(int boneIndex, float value); // 0x00ca4e90
extern void popMatrixStack(); // 0x00c9eae0

// Global singleton check (DAT_01223508 + 0xf4)
extern void* gAnimationManager;

// Assume these structures based on usage
struct AnimSet {
    int count;                    // +0x0? Actually used as *puVar7, puVar7[10] is count of something
    AnimBoneController** firstBone; // +0x0? Actually firstBone is *puVar7 (pointer to first controller)
    // offsets not fully known
};

struct AnimBoneController {
    int controllerCount;         // +0x12
    AnimKeyframe* firstKeyframe; // +0x0? (iVar4)
    int boneId;                  // +0x11
    AnimBoneController* next;    // +0x13
};

struct AnimKeyframe {
    float value;                 // +0x28
    int boneIndex;               // +0x24
    AnimKeyframe* next;          // +0x2c
};

struct ValidationContext {
    int* idArray;          // +0x4? Actually param_2+0x4 is an array of ints
    int* idPtr;            // +0x8? Actually param_2+0x8 is pointer to array of bone IDs
    uint32_t idCount;      // +0xc
    int* something;        // +0x14 (array of structs with +0x18, +0x2d)
    uint32_t animSetId;    // +0x2c
};

uint8_t __thiscall AnimationManager::validateAnimationBlending(void* thisPtr, ValidationContext* ctx)
{
    uint8_t result = 1;
    uint8_t localResult = 1;

    if (gAnimationManager != nullptr) {
        AnimSet* animSet = (AnimSet*)getAnimationSet(ctx->animSetId);
        if (animSet != nullptr) {
            int outerLoop = 5; // some recursive depth? Possibly hierarchy level
            do {
                int controllerGroupCount = animSet->count; // +0x28? Actually puVar7[10] (offset 0x28 from start)
                bool hasControllers = (controllerGroupCount != 0);
                if (hasControllers) {
                    AnimBoneController* boneCtrl = animSet->firstBone; // *puVar7
                    while (hasControllers) {
                        if (boneCtrl != nullptr) {
                            int keyframeCount = boneCtrl->controllerCount; // +0x12
                            bool hasKeyframes = (keyframeCount != 0);
                            if (hasKeyframes) {
                                AnimKeyframe* keyframe = boneCtrl->firstKeyframe; // *boneCtrl
                                while (hasKeyframes) {
                                    if (keyframe != nullptr) {
                                        uint32_t idx = 0;
                                        if (ctx->idCount != 0) {
                                            int* idIter = ctx->idPtr; // +0x8
                                            do {
                                                if (*idIter == boneCtrl->boneId) { // +0x11
                                                    // Found matching bone ID in validation list
                                                    int* targetData = *(int**)(ctx->something + 4 + idx * 0xc); // +0x14, offset 4 then idx*0xc
                                                    AnimBoneController* savedCtrl = boneCtrl;
                                                    if (*(int*)(ctx->idArray + idx * 4) != 0) { // +0x4, array of ints? Maybe flags
                                                        float value = keyframe->value; // +0x28
                                                        int boneIndex = keyframe->boneIndex; // +0x24
                                                        pushMatrixStack();
                                                        // Access target skeleton data: +0x18 from targetData, then (byte at +0x2d + boneIndex) * 0x28
                                                        int* targetBase = (int*)(*(int*)(targetData + 0x18) + ((uint8_t)(*(uint8_t*)(targetData + 0x2d)) + boneIndex) * 0x28);
                                                        if ((double)value < *(double*)(targetBase + 0x10) || 
                                                            *(double*)(targetBase + 0x18) < (double)value) {
                                                            localResult = 0; // Out of joint range
                                                        } else {
                                                            applyBoneTransform(boneIndex, value);
                                                        }
                                                        popMatrixStack();
                                                    }
                                                    boneCtrl = savedCtrl;
                                                    break;
                                                }
                                                idx++;
                                                idIter++;
                                            } while (idx < ctx->idCount);
                                        }
                                    }
                                    keyframeCount--;
                                    hasKeyframes = (keyframeCount != 0);
                                    keyframe = keyframe->next; // +0x2c
                                }
                            }
                        }
                        boneCtrl = boneCtrl->next; // +0x13
                    }
                }
                outerLoop--;
                result = localResult;
            } while (outerLoop != 0);
        }
    }
    return result;
}