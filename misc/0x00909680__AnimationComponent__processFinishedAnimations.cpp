// FUNC_NAME: AnimationComponent::processFinishedAnimations

#include <cstdint>

// Constants from global data
extern float DAT_00d5c454;   // Time scaling factor
extern uint32_t DAT_01205224; // Maximum count threshold

// External function declarations (assumed from game code)
extern bool FUN_00909590(void);                              // isPlaying
extern void FUN_004daf90(uint32_t* ptr);                     // delete/release
extern float FUN_006bff90(uint32_t offset);                 // getTime
extern int FUN_00471610(void);                               // getSlotManager
extern bool FUN_006c0050(float* timer, int unused1, int unused2); // resetTimer
extern void FUN_004088c0(void* object);                     // destroyObject

// Offset constants
const int kArrayBase = 0x70;
const int kArrayStride = 8;      // Two ints per slot
const int kNumSlots = 6;
const int kTimeField = 0xa4;
const int kDurationField = 200;  // +0xC8
const int kFlagsField = 0xb4;
const int kCountField = 0xb0;
const int kCallbackPtrField = 100; // +0x64
const int kInvalidSlotID = 0x48;    // 72

// Bit definitions for flags at +0xb4
const uint32_t kFlagFinished   = 1 << 0;  // bit 0
const uint32_t kFlagProcessing = 1 << 2;  // bit 2

uint32_t __fastcall AnimationComponent::processFinishedAnimations(void)
{
    bool isActive = FUN_00909590();
    if (!isActive) {
        uint32_t flags = *(uint32_t*)(this + kFlagsField);
        if ((flags & kFlagProcessing) == 0) {
            // Clear finished flag
            *(uint32_t*)(this + kFlagsField) = flags & ~kFlagFinished;
            if (*(int*)(this + kCallbackPtrField) != 0) {
                FUN_004daf90((uint32_t*)(this + kCallbackPtrField));
                *(uint32_t*)(this + kCallbackPtrField) = 0;
            }
            return 1; // Successfully cleared
        }
        // Clear processing flag
        *(uint32_t*)(this + kFlagsField) = flags & ~kFlagProcessing;
    }
    else if (*(uint32_t*)(this + kCountField) < DAT_01205224) {
        float currentTime = FUN_006bff90(this + kTimeField);
        float duration = *(float*)(this + kDurationField);
        if (duration <= currentTime) {
            float timeThreshold = duration * DAT_00d5c454;
            int* slotPtr = (int*)(this + kArrayBase);
            int slotIndex = kNumSlots;

            do {
                int slotId = *slotPtr;
                if (slotId != 0 && slotId != kInvalidSlotID) {
                    int slotManager = FUN_00471610();
                    float slotTime = FUN_006bff90(slotManager + 0x30);
                    if (slotTime < timeThreshold) {
                        bool resetResult = FUN_006c0050((float*)(slotManager + 0x30), 0, 0);
                        if (resetResult == false) {
                            goto continueLoop;
                        }
                        FUN_004088c0((void*)(slotId - 0xc));
                        // Set finished and processing flags
                        *(uint32_t*)(this + kFlagsField) |= (kFlagFinished | kFlagProcessing);
                    }
                }
continueLoop:
                slotPtr += 2; // Advance by two ints (8 bytes)
                slotIndex--;
            } while (slotIndex != 0);

            return 0; // All slots processed
        }
    }
    return 0; // No action taken
}