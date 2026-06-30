// FUNC_NAME: AnimationMixer::accumulateBlendResults

// 0x00578d30 - AnimationMixer::accumulateBlendResults
// Processes a set of animation tracks (children) and blends their poses into an output pose.
// The input 'this' (param_1) is a blend node container with a list of tracks (size 0xE0 each).
// The output 'pose' (param_2) is a 2-channel pose structure (each channel: position xyz + scale).
// Uses a sliding window over the track list, accumulating blended contributions.

#include <cstdint>

class AnimationMixer;

// Forward declarations of helper functions (callees)
uint32_t getGlobalFlags();                   // FUN_00571070
int32_t getTrackCount(AnimationMixer*);      // FUN_00579170
void sampleTrack(AnimationMixer*, void*);    // FUN_00581d70 - samples a track
void blendChannels(float* output, float alpha); // FUN_005781f0 - blends two channels with alpha
void accumulatePose(float* outA, float* in, float* outB); // FUN_0056cba0 - adds channel data

// Constants (likely defined elsewhere)
extern const float kIdentityScale = 1.0f;    // DAT_00e2b1a4
extern const float kTimeScale = 0.016f;      // DAT_00e2afac (example)
extern const float kTimeOffset = 0.0f;       // DAT_00e2a850 (example)
extern const float kSpeedFactor = 1.0f;      // DAT_00e2cd54 (example)

struct AnimationTrack {
    // vtable at offset 0, virtual method at +0x10 (likely getPose or sample)
    uint32_t vtable;                    // +0x00
    // ... other fields
    int32_t startTime;                  // +0x1c (index 7)
    int32_t duration;                   // +0x1c? Actually there's two ints: [0x1e] and [0x1f] = start/end?
    int32_t playbackType;               // +0x80 (index 0x20)
    char hasWeight;                     // +0x70 (index 0x1c)
    // ... rest is 0xE0 total size
};

// Output pose structure (size 0x30 bytes)
struct BlendPose {
    // Channel 0 (source pose?)
    float posX;      // +0x00? Actually param_2+0x10 is first channel
    float posY;      // +0x14
    float posZ;      // +0x18
    float scale;     // +0x1c
    // Channel 1 (blended result)
    float blendX;    // +0x20
    float blendY;    // +0x24
    float blendZ;    // +0x28
    float blendScale;// +0x2c
};

// This is the function at 0x578d30
int __thiscall AnimationMixer::accumulateBlendResults(int thisPtr, BlendPose* outputPose)
{
    int trackCount;
    uint32_t flags;
    int iter;
    AnimationTrack* prevTrack;
    AnimationTrack* currTrack;
    float timeDelta;
    float alpha;
    float duration;
    float fVar8; // cached kIdentityScale
    uint32_t localFlags; // from getGlobalFlags()
    // Local structs used to pass to helper functions
    struct SampleInput {
        AnimationMixer* mixer;
        float param1;
        float param2;
        // ... more floats to fill 36 bytes? Actual layout from code: local_a0 (mixer), local_9c (float), local_98 (float), local_90..fStack_74 (8 floats)
    } sampleInput;
    struct BlendInput {
        AnimationMixer* mixer;
        float param1; // local_5c
        float param2; // local_58
        // then 8 floats local_50..local_34? Actually local_50, local_4c, local_48, local_44, local_40, local_3c, local_38, local_34
    } blendInput;
    struct Temp8Floats {
        float arr[8]; // corresponds to fStack_30..fStack_14
    } tempBlend;

    // Check if blending is disabled or no tracks
    flags = *(uint32_t*)(thisPtr + 0x10);
    if (((flags >> 20) & 1) != 0) {
        // Skip blending, just clear/output zeros
        return sampleTrack(thisPtr, outputPose); // FUN_00581d70
    }

    trackCount = getTrackCount(); // FUN_00579170
    if (trackCount == 0) {
        return sampleTrack(thisPtr, outputPose);
    }

    fVar8 = kIdentityScale; // 1.0f

    // Initialize output pose channel 0 to identity (zero position, scale 1)
    outputPose->posX = 0.0f;
    outputPose->posY = 0.0f;
    outputPose->posZ = 0.0f;
    outputPose->scale = fVar8;

    // Initialize output pose channel 1 to identity
    outputPose->blendX = 0.0f;
    outputPose->blendY = 0.0f;
    outputPose->blendZ = 0.0f;
    outputPose->blendScale = fVar8;

    timeDelta = 0.0f; // local_b4
    localFlags = getGlobalFlags(); // FUN_00571070
    prevTrack = nullptr;
    iter = 0;

    if (trackCount > 0) {
        do {
            // Compute index into track array (circular buffer)
            int32_t baseIndex = (thisPtr + 0x2ec); // pointer to track array
            int32_t countField = *(int32_t*)(thisPtr + 0x2e4); // total capacity
            int32_t offsetField = *(int32_t*)(thisPtr + 0x2e8); // some offset
            int32_t index = ((countField - trackCount) + iter + 1 + offsetField) % countField;
            currTrack = (AnimationTrack*)(baseIndex + index * 0xE0); // 0xE0 stride

            if (prevTrack != nullptr) {
                // Compute time delta from previous track's duration
                timeDelta = (float)(*(int32_t*)(prevTrack + 0x7c) - *(int32_t*)(prevTrack + 0x78)); // duration = end - start
                // Setup sampleInput struct for previous track
                sampleInput.mixer = thisPtr; // local_a0
                sampleInput.param1 = *(float*)(thisPtr + 0x1c); // local_9c - some time offset
                sampleInput.param2 = *(float*)(thisPtr + 0x24) - fVar8; // local_98 - another time offset
                // Clear the 8 float payload
                sampleInput.pad[0] = 0.0f; // local_90
                sampleInput.pad[1] = 0.0f; // local_8c
                sampleInput.pad[2] = 0.0f; // local_88
                sampleInput.pad[3] = fVar8; // local_84
                sampleInput.pad[4] = 0.0f; // local_80
                sampleInput.pad[5] = 0.0f; // fStack_7c
                sampleInput.pad[6] = 0.0f; // fStack_78
                sampleInput.pad[7] = fVar8; // fStack_74

                alpha = 0.0f; // local_a4
                if (*(char*)(prevTrack + 0x70) != 0) { // if weight flag set
                    // Blend alpha based on weight
                    float weightRatio = (float)(*(int32_t*)(prevTrack + 0x78)) / (float)(*(int32_t*)(prevTrack + 0x7c));
                    alpha = (float)((double)(weightRatio * kTimeScale - kTimeOffset));
                    // Call math function (maybe sin/cos?)
                    FUN_00b99fcb(); // placeholder
                    alpha = (alpha + kIdentityScale) * kSpeedFactor;
                }

                // Update flags based on playback type
                uint32_t flags2 = localFlags;
                if (*(int32_t*)(prevTrack + 0x80) == 2) {
                    flags2 |= 0x100;
                }

                if ((flags2 & 0x100) == 0) {
                    // Sample previous track's pose
                    sampleInput.param1 = (float)(*(int32_t*)(prevTrack + 0x1c)); // track start time
                    sampleInput.param2 = (float)(*(int32_t*)(prevTrack + 0x1c)) + timeDelta; // end time
                    // Call virtual method (vtable+0x10) on prevTrack
                    (*(void (__thiscall**)(int))(*(uint32_t*)prevTrack + 0x10))(&sampleInput);
                }

                // Setup blendInput for current track
                blendInput.mixer = thisPtr; // local_60
                // Set initial blendInput floats to zero/identity
                blendInput.pad0 = 0.0f; // local_50
                blendInput.pad1 = 0.0f; // local_4c
                blendInput.pad2 = 0.0f; // local_48
                blendInput.pad3 = fVar8; // local_44
                blendInput.pad4 = 0.0f; // local_40
                blendInput.pad5 = 0.0f; // local_3c
                blendInput.pad6 = 0.0f; // local_38
                blendInput.pad7 = fVar8; // local_34

                if (iter == trackCount) {
                    // Last element: use own data?
                    blendInput.param1 = *(float*)(thisPtr + 0x1c); // local_5c
                    blendInput.param2 = blendInput.param1 + timeDelta; // local_58
                    sampleTrack(thisPtr, &blendInput); // FUN_00581d70
                } else {
                    // Sample current track's pose via virtual call
                    blendInput.param1 = (float)(*(int32_t*)(currTrack + 0x1c)); // local_5c
                    blendInput.param2 = (float)(*(int32_t*)(currTrack + 0x1c)) + timeDelta; // local_58
                    (*(void (__thiscall**)(int))(*(uint32_t*)currTrack + 0x10))(); // virtual call
                }

                // Now blend or copy based on flags
                if ((flags2 & 0x100) == 0) {
                    // Blend with alpha
                    blendChannels(&tempBlend.arr[0], alpha); // FUN_005781f0
                    // restore thisPtr (was saved in local_64)
                    // currTrack was saved in local_6c
                } else {
                    // Copy previous blendInput results to tempBlend
                    tempBlend.arr[0] = blendInput.pad0; // local_50
                    tempBlend.arr[1] = blendInput.pad1; // local_4c
                    tempBlend.arr[2] = blendInput.pad2; // local_48
                    tempBlend.arr[3] = blendInput.pad3; // local_44
                    tempBlend.arr[4] = blendInput.pad4; // local_40
                    tempBlend.arr[5] = blendInput.pad5; // local_3c
                    tempBlend.arr[6] = blendInput.pad6; // local_38
                    tempBlend.arr[7] = blendInput.pad7; // local_34
                }

                // Accumulate tempBlend into output pose channel 0
                accumulatePose(&outputPose->posX, &tempBlend.arr[0], &outputPose->posX); // FUN_0056cba0
                // Add the second half of tempBlend (indices 4-7) to output pose channel 1
                outputPose->blendX += tempBlend.arr[4];
                outputPose->blendY += tempBlend.arr[5];
                outputPose->blendZ += tempBlend.arr[6];
                outputPose->blendScale += tempBlend.arr[7];
                // Reset scale to identity after accumulation? The code sets outputPose->blendScale = fVar8 after addition (odd)
                outputPose->blendScale = fVar8;
            }

            iter++;
            prevTrack = currTrack;
        } while (iter <= trackCount);
    }

    // Final sample of own track (?) using the last timeDelta
    // Setup sampleInput again
    sampleInput.mixer = thisPtr;
    sampleInput.param1 = *(float*)(thisPtr + 0x1c) + timeDelta; // local_9c
    sampleInput.param2 = *(float*)(thisPtr + 0x24) - fVar8; // local_98
    // Clear payload
    sampleInput.pad[0] = 0.0f;
    sampleInput.pad[1] = 0.0f;
    sampleInput.pad[2] = 0.0f;
    sampleInput.pad[3] = fVar8;
    sampleInput.pad[4] = 0.0f;
    sampleInput.pad[5] = 0.0f;
    sampleInput.pad[6] = 0.0f;
    sampleInput.pad[7] = fVar8;
    // Sample
    sampleTrack(thisPtr, &sampleInput); // FUN_00581d70
    // Accumulate sampleInput's payload into output pose
    accumulatePose(&outputPose->posX, &sampleInput.pad[0], &outputPose->posX);
    outputPose->blendX += sampleInput.pad[4];
    outputPose->blendY += sampleInput.pad[5];
    outputPose->blendZ += sampleInput.pad[6];
    outputPose->blendScale += sampleInput.pad[7];
    outputPose->blendScale = kIdentityScale;

    return 1;
}