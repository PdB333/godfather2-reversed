// FUNC_NAME: AnimationNode::evaluateAnimationNode

#include <cstdint>

// Constants
constexpr float ANIMATION_FRAME_TIME = 0.03333333f; // DAT_00e2b1a4 (approx 1/30)

// Structure for animation track data (param_4)
struct AnimationTrack {
    float* keyframeData; // +0x00
    int32_t numKeyframes; // +0x04
};

// Structure for animation node state (param_3)
struct AnimationNodeState {
    int8_t version; // +0x00 (compared at +1)
    uint32_t* currentFrame; // +0x04 (pointer to array of 4 uint32s)
    // currentFrame[0] = frameIndex, [1] = flags, [2] = blendFrom, [3] = blendDuration
    uint8_t** typeTable; // +0x0c (second pointer to byte used for dispatch)
};

// Forward declarations of helper functions (from other modules)
void clampFloatToZero(float* value);                // FUN_00591c00
void updateAnimationBlend();                         // FUN_00593700 (no parameters)
float* getAnimationTrackData(AnimationTrack* track); // FUN_0058abc0

// External dispatch table indexed by (typeByte & 0x3F) (DAT_0103afc0)
typedef void* AnimationTypeFuncPtr;
extern AnimationTypeFuncPtr g_animationTypeDispatchTable[0x23]; // 35 entries

// Main function
int32_t AnimationNode::evaluateAnimationNode(
    float time,
    void* entity,              // param_2 (pointer to game object with offset 0x7c)
    AnimationNodeState* state, // param_3
    AnimationTrack* track,     // param_4
    float startVal,            // param_5
    float endVal,              // param_6
    uint32_t flags,           // param_7
    float param8              // param_8
)
{
    if (state->version < 1) {
        return 0;
    }

    uint32_t* frameState = state->currentFrame; // gets pointer from +4
    uint32_t frameIndex = frameState[0];

    float blendedTime = time;

    // Check if frameIndex is within valid range
    if (track->numKeyframes <= frameIndex) {
        float zero = 0.0f;
        clampFloatToZero(&zero);
        blendedTime = 0.0f;
    }

    float sampleValue = *(float*)(track->keyframeData + frameIndex * 4); // float from keyframe array

    // Condition for special blend handling: flags bit 2 clear, no flag on frameState[1], entity bits set
    if (((flags & 4) == 0) &&
        (frameState[1] == 0) &&
        ((*(uint8_t*)(*(int32_t*)((char*)entity + 0x7c) + 0x10) & 1) != 0) &&
        (*(char*)(*(int32_t*)((char*)entity + 0x7c) + 0x30) != 0))
    {
        updateAnimationBlend();
        blendedTime = (float)(blendedTime * frameState[3]) + (float)frameState[2];
        float* trackData = getAnimationTrackData(track);
        *trackData = blendedTime;
        sampleValue = blendedTime;
    }

    if (sampleValue <= 0.0f) {
        sampleValue = ANIMATION_FRAME_TIME;
    }

    uint8_t typeByte = *state->typeTable[0];
    if ((typeByte & 0x3F) < 0x23) {
        float scale = ANIMATION_FRAME_TIME / sampleValue;
        // Dispatch to animation type handler
        auto handler = reinterpret_cast<void*(__thiscall*)(void*, uint8_t*, AnimationTrack*, float, float, uint32_t, float)>
            (g_animationTypeDispatchTable[typeByte & 0x3F]);
        return handler(
            entity,                   // this pointer for the handler call
            state->typeTable,         // second parameter (same as type table pointer)
            track,
            scale * startVal,
            scale * endVal,
            flags,
            scale * param8
        );
    }

    return 0;
}