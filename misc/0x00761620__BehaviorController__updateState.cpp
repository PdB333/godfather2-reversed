// FUNC_NAME: BehaviorController::updateState

#include <cstdint>

// Forward declarations and structures
struct Vec3 {
    float x, y, z;
};

// Unknown functions - forward declarations
extern int SimManager_GetInstance(); // FUN_00471610
extern void Animation_Play(int obj, int animId, float param, int flags, int something, int player); // FUN_00760190
extern void ReleasePointer(int* ptr); // FUN_004daf90
extern void InterpolateTransform(int target, float blend, Vec3* transform); // FUN_009a4a90
extern void StopEffect(int* handle); // FUN_005f7ba0
extern void ProcessAnimations(); // FUN_00760210
extern void SetState(int state); // FUN_005fdee0
extern void SetTransform(int obj, Vec3* transform, int zero1, int zero2, int zero3); // FUN_00600a40

// Global constants (guessed)
extern int g_player; // DAT_00e51b3c
extern int* g_resourceManager; // DAT_012233a0 + 4 offset, pointer to pointer
extern float g_defaultBlend; // DAT_00e44634 (likely 1.0f)
extern void* g_nextStateFunc; // LAB_007611e0 (address of another state function)

int BehaviorController::updateState(int param_2) // __thiscall
{
    int pBehaviorData = *(int*)(this + 0x5C); // pointer to behavior data (e.g. animation controller)
    int simManager = SimManager_GetInstance(); // get singleton
    Vec3 currentTransform;
    currentTransform = *(Vec3*)(simManager + 0x30); // some transform from world manager (e.g. current time?)
    // Note: second call to SimManager_GetInstance() may be ignored, or used for side effect
    SimManager_GetInstance();

    int pTargetObject = *(int*)(this + 0x70); // pointer to targeted object or sub-object (e.g. rigid body)
    if (pTargetObject != 0) {
        float blendFactor = *(float*)(this + 0x78); // blend factor (e.g. interpolation factor)
        uint32_t flags = *(uint32_t*)(this + 0x88);
        if ((flags >> 4) & 1) == 0) { // if bit4 (e.g., "isEnabled") not set
            // Play animation on behavior data
            Animation_Play(pBehaviorData, 8, *(float*)(pBehaviorData + 0x5C4), 0, 2, g_player);

            // Update resource reference (smart pointer / intrusive list management)
            int* pResourceManager = *(int**)g_resourceManager; // read pointer at offset 4 of global
            int pNewResource;
            if (pResourceManager == 0 || pResourceManager == (int*)0x1F30) {
                pNewResource = 0;
            } else {
                pNewResource = (int)(pResourceManager - 0x1EE8); // adjust pointer
            }

            int* pCurrentResource = &local_1c; // local smart pointer variable
            if (pCurrentResource != pNewResource) {
                if (pCurrentResource != 0) {
                    ReleasePointer(pCurrentResource);
                }
                pCurrentResource = pNewResource;
                if (pNewResource != 0) {
                    *(int*)(pNewResource + 4) = (int)&local_1c; // link to intrusive list
                }
            }

            // Interpolate target object's transform towards currentTransform using blendFactor
            InterpolateTransform(pTargetObject, blendFactor, &currentTransform);

            // Stop any running effects (sound/etc)
            if (local_38[0] != 0 && local_30 != 0) {
                StopEffect(local_38);
                StopEffect(local_2c);
            }

            // Process animations globally
            ProcessAnimations();
        }
    }

    // Set flag on behavior data (e.g., "state completed")
    *(uint32_t*)(pBehaviorData + 0x564) |= 4;

    // Set next state
    SetState(param_2); // transitions to a new state (param_2 might be state ID)
    *(float*)(pBehaviorData + 0x560) = g_defaultBlend; // store default blend
    *(void**)(pBehaviorData + 0x550) = g_nextStateFunc; // set next state function pointer

    // Set target transform (possibly finalizing position)
    SetTransform(this + 0x70, &currentTransform, 0, 0, 0);

    return 0;
}