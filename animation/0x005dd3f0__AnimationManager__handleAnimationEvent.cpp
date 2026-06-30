// FUNC_NAME: AnimationManager::handleAnimationEvent
// Function address: 0x005dd3f0
// Role: Process an animation event; either update an existing slot or allocate a new one.
// The object has two arrays of 5 animation event slots (each 0x68 bytes).
// Slots at +0x18 are used for matching; slots at +0xc are free list? (empty if first int == -1)
// The parameter in ESI (EDX?) is an AnimationEvent structure containing event data.

#include <cstdint>

// Forward declaration of the helper function (sets up animation parameters)
void setupAnimation(float param, int sampleRate); // FUN_005dd0d0

// Structure for an animation event slot (size 0x68 = 26 ints)
struct AnimationSlot {
    int32_t field_0;       // +0x00
    int32_t field_4;       // +0x04
    int32_t field_8;       // +0x08
    int32_t id1;           // +0x0c  (matching key)
    int32_t id2;           // +0x10  (matching key)
    int32_t id3;           // +0x14  (matching key)
    int32_t id4;           // +0x18  (matching key)
    int32_t id5;           // +0x1c  (matching key)
    uint8_t inUse;         // +0x22  (byte flag)
    // ... other fields ...
    int32_t field_44;      // +0x44
    // Many more fields to reach 0x68 bytes (26 ints)
};

// The owner class (AnimationManager) contains two arrays of 5 slots each.
// Offsets are relative to 'this' (EDI).
class AnimationManager {
public:
    // +0x00... slots at +0x0c and +0x18
    // +0x214: some index
    // +0x240: some float parameter
    // +0x254: some int parameter
    // +0x27c, +0x280: float outputs
    int32_t unk_214;
    float param_240;
    int32_t param_254;
    float output_27c;
    float output_280;

    // The two arrays are at offsets 0x0c and 0x18 from this pointer.
    // Because of alignment, they are not at fixed offsets in this struct.
    // We'll compute addresses manually.

    int handleAnimationEvent(void* event); // param in ESI is an AnimationEvent*
};

// The AnimationEvent structure expected from the caller.
struct AnimationEvent {
    int32_t field_04;  // +0x04 (float? but stored as int32)
    int32_t field_08;  // +0x08
    int32_t field_0c;  // +0x0c
    int32_t field_10;  // +0x10
    int32_t field_1c;  // +0x1c (flag)
    int32_t field_20;  // +0x20 (match key1)
    int32_t field_24;  // +0x24 (match key2)
    int32_t field_28;  // +0x28 (match key3)
    int32_t field_2c;  // +0x2c (match key4)
    int32_t field_34;  // +0x34 (value to store)
};

int AnimationManager::handleAnimationEvent(void* event) {
    AnimationEvent* animEvent = (AnimationEvent*)event;
    int32_t* slotBase;
    uint32_t idx;

    // if flag == 0, try to find a matching slot in the first array (at +0x18)
    if (animEvent->field_1c == 0) {
        // Start at +0x18 (5 slots, each 0x68 bytes = 26 ints)
        slotBase = (int32_t*)((uint8_t*)this + 0x18);
        idx = 0;
        do {
            // Check if slot is valid (id1 != -1) and matches all four keys
            if ((slotBase[-3] != -1) &&                          // id1 at +0x0c
                (slotBase[-2] == animEvent->field_20) &&         // id2 at +0x10
                (slotBase[-1] == animEvent->field_24) &&         // id3 at +0x14
                (slotBase[0] == animEvent->field_28) &&          // id4 at +0x18
                (slotBase[1] == animEvent->field_2c))            // id5 at +0x1c
            {
                // Found matching slot
                uint8_t* inUseFlag = (uint8_t*)((int32_t)slotBase + 10); // +0x22
                if (*inUseFlag == 0) {
                    // Slot already completed – just return success
                    return 1;
                }
                // Slot is in use; mark it as completed
                *inUseFlag = 0;
                // Update offset values from event
                slotBase[-6] = animEvent->field_0c;   // +0x00
                slotBase[-5] = animEvent->field_10;   // +0x04
                slotBase[11] = animEvent->field_34;   // +0x44
                return 1;
            }
            idx++;
            slotBase += 26; // next slot (26 ints = 0x68 bytes)
        } while (idx < 5);

        // No match found; try to allocate a new slot from the second array (at +0x0c)
        slotBase = (int32_t*)((uint8_t*)this + 0x0c);
        idx = 0;
        do {
            if (*slotBase == -1) {
                // Found an empty slot (first int is -1)
                break;
            }
            idx++;
            slotBase += 26;
        } while (idx < 5);

        if (idx == 5) {
            // All slots full, cannot allocate
            // (falls through to return 1 without doing anything)
        } else {
            // Allocate the empty slot by calling setupAnimation with default parameters
            setupAnimation(1.0f, 96000);
        }
    }
    else {
        // Force reset/update regardless of matching
        float param1 = 1.0f;
        int param2 = 96000;
        if (this->unk_214 != -1) {
            param1 = this->param_240;
            param2 = this->param_254;
        }
        setupAnimation(param1, param2);

        // Update output floats from event if non-negative
        if (*(float*)&animEvent->field_04 >= 0.0f) {
            this->output_27c = *(float*)&animEvent->field_04;
        }
        if (*(float*)&animEvent->field_08 >= 0.0f) {
            this->output_280 = *(float*)&animEvent->field_08;
        }
    }
    return 1;
}