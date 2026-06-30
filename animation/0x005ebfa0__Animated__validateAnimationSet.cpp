// FUNC_NAME: Animated::validateAnimationSet

#include <cstdint>

// Forward declarations of external functions (guessed signatures)
// These are likely member functions of related classes.
class AnimationSet;
class AnimationKeyframeData;

// Returns a pointer to an AnimationSet from some object ID (param_2)
AnimationSet* getAnimationSet(uint32_t id);

// Given a keyframe ID, returns a pointer to keyframe data structure via output parameter.
// Returns 0 on failure, non-zero on success.
int findKeyframeData(uint32_t keyframeId, AnimationKeyframeData*& outData);

// Lock/unlock animation data mutex (EARS threading)
void lockAnimationData();
void unlockAnimationData();

// Seek to a specific time on an animation track (trackIndex, time)
void seekAnimationTime(int trackIndex, float time);

// Structure representing an animation within an AnimationSet
struct AnimationEntry {
    uint32_t field_0x54; // Keyframe ID or some identifier
    int field_0x5c;      // Track index or sub-index
    float field_0x60;    // Target time
    // ... other fields
};

// Structure for AnimationSet
struct AnimationSet {
    AnimationEntry** m_animationList; // +0x270: array of pointers to AnimationEntry
    uint32_t m_animationCount;        // +0x274: number of entries
    // ... other fields
};

// Structure for keyframe data returned by findKeyframeData
struct AnimationKeyframeData {
    uint8_t field_0x18[0x28];       // +0x18: base of an array of keyframe time ranges (size 0x28 each)
    uint8_t field_0x2d;             // +0x2d: offset index into the array (used as additive to trackIndex)
    // Also likely has fields at +0x10 (low) and +0x18 (high) within each element of the array
};

// The function itself
bool __thiscall Animated::validateAnimationSet(void* thisPtr, uint32_t animationSetId) {
    // Offsets based on analysis:
    struct Animated {
        uint32_t unused[0x56c/4];               // up to +0x56c
        AnimationSet* m_pCurrentAnimationSet;   // +0x56c
        // padding or other fields
        AnimationSet* m_pAnimationSet;          // +0x580
    };

    Animated* self = static_cast<Animated*>(thisPtr);

    // Both pointers must be non-null
    if (self->m_pCurrentAnimationSet == nullptr || self->m_pAnimationSet == nullptr) {
        return false;
    }

    // If animationSetId is non-zero, validate individual animations in the set
    if (animationSetId != 0) {
        AnimationSet* animSet = getAnimationSet(animationSetId);
        if (animSet == nullptr) {
            // Return true? Actually the original code returns 1 if animSet is null? Wait: code has:
            // if (param_2 != 0) { ... } and if local_14 != 0 then loop, else returns 1.
            // So if getAnimationSet returns 0 or the count is 0, it returns 1 (true).
            return true;
        }

        uint32_t count = animSet->m_animationCount;
        if (count == 0) {
            return true;
        }

        // Iterate over all animations in the set
        bool allValid = true;
        for (uint32_t i = 0; i < count; ++i) {
            AnimationEntry* anim = animSet->m_animationList[i];
            if (anim == nullptr) {
                allValid = false;
                continue;
            }

            float targetTime = anim->field_0x60;
            int trackIndex = anim->field_0x5c;
            uint32_t keyframeId = anim->field_0x54;

            // Get keyframe data pointer
            AnimationKeyframeData* keyframeData = nullptr;
            int result = findKeyframeData(keyframeId, keyframeData);
            if (result == 0 || keyframeData == nullptr) {
                allValid = false;
                continue;
            }

            lockAnimationData();

            // Calculate pointer to a time range structure within keyframe data
            // formula: (keyframeData + 0x18) + ((byte at keyframeData+0x2d) + trackIndex) * 0x28
            uint8_t baseIndex = keyframeData->field_0x2d;
            uint32_t adjustedIndex = static_cast<uint32_t>(baseIndex) + trackIndex;
            // Element size is 0x28 bytes
            uint8_t* timeRangeBase = reinterpret_cast<uint8_t*>(keyframeData) + 0x18;
            // The time range struct likely has low and high at +0x10 and +0x18 relative to its start
            struct TimeRange {
                float low;   // +0x10
                float high;  // +0x18
            };
            TimeRange* range = reinterpret_cast<TimeRange*>(timeRangeBase + adjustedIndex * 0x28);

            // Check if targetTime is within the range (double comparison)
            if (static_cast<double>(targetTime) < static_cast<double>(range->low) ||
                static_cast<double>(range->high) < static_cast<double>(targetTime)) {
                allValid = false;
                unlockAnimationData();
                continue;
            }

            // Time is within range, seek to that time
            seekAnimationTime(trackIndex, targetTime);
            unlockAnimationData();
        }
        return allValid;
    }

    // If animationSetId is zero, return true (no validation needed)
    return true;
}