// FUNC_NAME: AnimationController::evaluateKeyframes

#include <cstdint>

// Forward declaration for unknown sampler function type
typedef void (__thiscall *SamplerFunc)(void* thisPtr, int index, float* outValue);

// Global sampler registry: array of { SamplerFunc func; /* padding? */ } with stride 0xC
extern SamplerFunc g_curveSamplers[0x01205570]; // need proper declaration
extern int32_t g_numCurveTypes; // DAT_01205574

// Structure for keyframe data passed as param_2
struct KeyframeIndices {
    int32_t indices[3];  // piVar1[0..2]
    int32_t outputSlot;  // piVar1[3]
};

// Output buffer structure
struct OutputBuffer {
    float* data;   // pointer to output float array
    uint32_t size; // number of elements in data
};

void AnimationController::evaluateKeyframes(float* this_, KeyframeIndices* keyData, OutputBuffer* output) {
    // Check if animation is not in a certain state (state == 2 might mean "stopped" or "finished")
    if (*(int32_t*)(*(int32_t*)((char*)this_ + 0x7c) + 0x2c) != 2) {
        int32_t* idxArray = keyData->indices; // piVar1
        int32_t i0 = idxArray[0];
        int32_t i1 = idxArray[1];
        int32_t i2 = idxArray[2];

        float v0, v1, v2; // local_8[0], local_c, fStack_10

        // Sample three curve values using global function table
        if (i0 >= 0 && i0 < g_numCurveTypes && g_curveSamplers[i0] != nullptr) {
            g_curveSamplers[i0](this_, i0, &v0);
        }
        if (i1 >= 0 && i1 < g_numCurveTypes && g_curveSamplers[i1] != nullptr) {
            g_curveSamplers[i1](this_, i1, &v1);
        }
        if (i2 >= 0 && i2 < g_numCurveTypes && g_curveSamplers[i2] != nullptr) {
            g_curveSamplers[i2](this_, i2, &v2);
        }

        // Interpolation factor: (currentValue - start) / (end - start)
        float t = 0.0f;
        if (v2 > v1) {
            t = (v0 - v1) / (v2 - v1);
        }

        // Check if output slot is valid and possibly reset a weight/timer
        int32_t outputSlot = keyData->outputSlot;
        if (output->size <= (uint32_t)outputSlot) {
            float resetValue = 0.0f;
            FUN_00591c00(&resetValue); // unknown: likely resets a time or weight variable
        }

        // Store interpolated value in output buffer
        output->data[outputSlot] = t;
    }
}