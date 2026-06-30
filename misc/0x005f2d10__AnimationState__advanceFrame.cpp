// FUNC_NAME: AnimationState::advanceFrame
// Address: 0x005f2d10
// Role: Advances the current frame index for an animation state, handling wrapping and special cases for type 2 and 3 frames.
// The function reads frame parameters from a structure pointed to by this+0x8, and updates this+0x66 and params->otherFrame.

// External globals (likely used for deterministic pseudo-random sequence)
extern int DAT_010c2678;     // mask
extern int DAT_012054b4;     // global counter for "random" table lookup
extern float DAT_00e2cd54;   // constant (0.5f? used for offset)
extern float DAT_010c2680[]; // array of random values

// Frame parameters structure at this+0x8
struct AnimationFrameParams {
    uint8_t unknown_0;   // +0x0
    uint8_t frameType;   // +0x1
    uint8_t numFrames;   // +0x2
    uint8_t padding_3;   // +0x3
    uint8_t otherFrame;  // +0x4
};

void AnimationState::advanceFrame() {
    // this in EDI
    if (this == nullptr) return;

    AnimationFrameParams* params = reinterpret_cast<AnimationFrameParams*>(
        *reinterpret_cast<uintptr_t*>(reinterpret_cast<uint8_t*>(this) + 0x8));
    if (params == nullptr) return;

    uint8_t numFrames = params->numFrames;
    if (numFrames < 2) {
        // Not enough frames; reset to first frame
        *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(this) + 0x66) = 0;
        return;
    }
    if (numFrames == 0) return;

    uint8_t newFrame;
    if (params->frameType < 4) {
        // Compute a candidate frame using deterministic pseudo-random
        uint32_t index = DAT_010c2678 & DAT_012054b4;
        DAT_012054b4++;
        float randVal = DAT_010c2680[index];
        float computed = ((static_cast<float>(numFrames) - DAT_00e2cd54 - DAT_00e2cd54) * randVal + DAT_00e2cd54);
        newFrame = static_cast<uint8_t>(static_cast<int>(computed));

        uint8_t compareFrame;
        if (params->frameType == 2) {
            compareFrame = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(this) + 0x66); // current frame
        } else if (params->frameType == 3) {
            compareFrame = params->otherFrame;
        } else {
            goto skipIncrement;
        }

        if (newFrame == compareFrame) {
            // If the computed frame matches the comparison, advance by one
            newFrame++;
        }
    } else {
        // For other types, simply increment the current frame
        newFrame = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(this) + 0x66);
        newFrame++;
    }

skipIncrement:
    // Wrap around if we exceed the number of frames
    if (numFrames <= newFrame) {
        newFrame = newFrame - numFrames;
    }

    // Store the new frame in both places
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(this) + 0x66) = newFrame;
    params->otherFrame = newFrame;
}