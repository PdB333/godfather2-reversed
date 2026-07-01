// FUNC_NAME: EmotionController::processEmotionEvent
// Address: 0x007ad250
// Role: Handles emotion events (new, clear, stop, update) for character facial expression system.
// Manages 20 emotion slots (+0x18 to +0xb0, 8 bytes each), current/target emotions, and timers.

#include <cstdint>

// Forward declarations for called functions (unknown implementations)
void processEmotionEvent(int* eventData); // FUN_0046c6a0
void releaseEmotionSlot(int32_t slotHandle); // FUN_00408680 - decrement ref or release
void stopEmotionSlot(int32_t slotHandle); // FUN_004086d0 - stop/remove
void resetToNeutral(uint32_t thisPtr); // FUN_004088c0 - apply neutral expression
int32_t getEmotionInstance(int32_t* emotionData, int32_t param); // FUN_00446100
uint32_t hashEmotionName(int32_t instance, uint32_t hash); // FUN_006bc8d0 - hash lookup
void playEmotionAnimation(uint32_t animHandle); // FUN_0044b210
int32_t findEmotionByHash(int32_t data, uint32_t hash); // FUN_006c9470
int32_t createEmotionInstance(); // FUN_00716c30
void clearTimerAt(uint32_t timerAddr, int32_t value); // FUN_00402050

// Constants
constexpr uint32_t EMOTION_SLOT_COUNT = 20;
constexpr uint32_t EMOTION_SLOT_SIZE = 8; // each slot is 8 bytes: +0x00 id, +0x04 weight/handle

// Global constant (DAT_0120e93c) - likely "invalid" or "neutral" emotion ID
extern uint32_t gNeutralEmotionID;

class EmotionController {
public:
    // Offsets from this:
    // +0x00 : vtable? skip
    // +0x18 to +0xb0 : 20 emotion slots (each 8 bytes, storing emotion ID and weight/handle)
    int32_t m_slotIDs[EMOTION_SLOT_COUNT]; // actually offset 0x18, 0x20, ... 0xb0 (8 bytes apart, but we only compare int at base)
    // Note: each slot occupies 8 bytes. The first int is the emotion ID, the second int is some data.
    // In code, only the first int is compared.
    int32_t padding_slots; // to reach 0xb8? Actually slots end at 0xb8? 0x18 + 20*8 = 0x18+0xa0 = 0xb8. So +0xb8 is after slots.
    // +0xb8 : flags (bool) - is emotion mode active?
    int8_t m_emotionModeActive; // +0xb8
    int32_t m_targetEmotion; // +0xbc - target emotion ID for blend
    int32_t m_currentEmotion; // +0xc4 - currently playing emotion ID
    int32_t m_currentSlotIndex; // +0xcc - 1-20, index of active slot
    int32_t m_blendTarget; // +0xd0 - handle or pointer to blend target
    int32_t m_timer1; // +0xd8
    int32_t m_timer2; // +0xdc
    int32_t m_timer3; // +0xe0
    int32_t m_timer4; // +0xe4
    uint32_t m_durationTimer; // +0xe8 - timer that gets cleared

    // Method at 0x007ad250
    void processEmotionEvent(int* eventData) {
        processEmotionEvent(eventData); // FUN_0046c6a0 - likely validates or initializes processing

        int32_t emotionID = *eventData;

        // Case 1: Neutral/Invalid emotion (gNeutralEmotionID)
        if (emotionID == gNeutralEmotionID) {
            FUN_004086d0(&gNeutralEmotionID); // stop neutral emotion
            if (!m_emotionModeActive) {
                if (m_blendTarget != 0) {
                    // release blend target
                    releaseEmotionSlot((int32_t*)&m_blendTarget);
                    m_blendTarget = 0;
                }
                // clear all four timers
                m_timer1 = 0;
                m_timer2 = 0;
                m_timer3 = 0;
                m_timer4 = 0;
                return;
            }
            // if emotion mode active and all timers zero -> reset to neutral
            if (m_timer1 == 0 && m_timer2 == 0 && m_timer3 == 0 && m_timer4 == 0) {
                uint32_t condition = (this != (EmotionController*)0x3c) ? ~0U : 0; // negative mask
                resetToNeutral(condition & (uint32_t)this);
                return;
            }
            // else get an emotion instance from timer1 and play its animation
            int32_t instance = getEmotionInstance(&m_timer1, 0); // maybe fetch by timer?
            if (instance == 0) return;
            uint32_t animHandle = hashEmotionName(instance, 0x369ac561);
            playEmotionAnimation(animHandle);
            return;
        }

        // Case 2: Target emotion (m_targetEmotion) -> clear all slots?
        if (emotionID == m_targetEmotion) {
            // Release all 20 slots (call FUN_00408680 on each)
            for (int i = 0; i < EMOTION_SLOT_COUNT; ++i) {
                releaseEmotionSlot((int32_t)(this) + 0x18 + i * EMOTION_SLOT_SIZE);
            }
            return;
        }

        // Case 3: Current emotion (m_currentEmotion) -> stop all slots?
        if (emotionID == m_currentEmotion) {
            // Stop all 20 slots (call FUN_004086d0 on each)
            for (int i = 0; i < EMOTION_SLOT_COUNT; ++i) {
                stopEmotionSlot((int32_t)(this) + 0x18 + i * EMOTION_SLOT_SIZE);
            }
            return;
        }

        // Case 4: Emotion ID matches one of the active slot IDs
        bool matchedSlot = false;
        for (int i = 0; i < EMOTION_SLOT_COUNT; ++i) {
            if (emotionID == m_slotIDs[i]) {
                matchedSlot = true;
                break;
            }
        }
        if (!matchedSlot) return;

        // Further processing for matched slot
        int32_t subData = eventData[1]; // second int in eventData
        int32_t* subDataPtr = (int32_t*)subData;
        if (subDataPtr[1] == 0) {
            // second field of subData is zero -> return
            return;
        }
        int32_t value1 = subDataPtr[1] - 0x48; // subtract 0x48
        if (value1 == 0) return;

        int32_t resultHandle = 0;
        int32_t searchResult = findEmotionByHash(value1, 0x383225a1);
        if (searchResult != 0) {
            // found via hash, create instance
            resultHandle = createEmotionInstance();
        } else {
            // alternative hash lookup
            int32_t altHandle = hashEmotionName(value1, 0x369ac561);
            if (altHandle != 0) {
                resultHandle = altHandle;
            }
        }
        int32_t newHandle = resultHandle;

        if (m_emotionModeActive) {
            // If emotion mode active and blendTarget is either 0 or 0x48
            if (m_blendTarget == 0 || m_blendTarget == 0x48) {
                uint32_t condition = (this != (EmotionController*)0x3c) ? ~0U : 0;
                resetToNeutral(condition & (uint32_t)this);
                return;
            }
            if (m_emotionModeActive) {
                int32_t currentTarget = 0;
                if (m_blendTarget == 0) {
                    currentTarget = 0;
                } else {
                    currentTarget = m_blendTarget - 0x48;
                }
                // Only continue if newHandle matches currentTarget
                if (newHandle != currentTarget) {
                    return;
                }
            }
        }

        // Final check: if emotionID matches a specific slot and the slot index is correct
        // The code below checks a long list of conditions: slot offset matches slot index (m_currentSlotIndex)
        bool correctSlot = false;
        if (emotionID == m_slotIDs[0] && m_currentSlotIndex == 1) correctSlot = true;
        else if (emotionID == m_slotIDs[1] && m_currentSlotIndex == 2) correctSlot = true;
        else if (emotionID == m_slotIDs[2] && m_currentSlotIndex == 3) correctSlot = true;
        else if (emotionID == m_slotIDs[3] && m_currentSlotIndex == 4) correctSlot = true;
        else if (emotionID == m_slotIDs[4] && m_currentSlotIndex == 5) correctSlot = true;
        else if (emotionID == m_slotIDs[5] && m_currentSlotIndex == 6) correctSlot = true;
        else if (emotionID == m_slotIDs[6] && m_currentSlotIndex == 7) correctSlot = true;
        else if (emotionID == m_slotIDs[7] && m_currentSlotIndex == 8) correctSlot = true;
        else if (emotionID == m_slotIDs[8] && m_currentSlotIndex == 9) correctSlot = true;
        else if (emotionID == m_slotIDs[9] && m_currentSlotIndex == 10) correctSlot = true;
        else if (emotionID == m_slotIDs[10] && m_currentSlotIndex == 11) correctSlot = true;
        else if (emotionID == m_slotIDs[11] && m_currentSlotIndex == 12) correctSlot = true;
        else if (emotionID == m_slotIDs[12] && m_currentSlotIndex == 13) correctSlot = true;
        else if (emotionID == m_slotIDs[13] && m_currentSlotIndex == 14) correctSlot = true;
        else if (emotionID == m_slotIDs[14] && m_currentSlotIndex == 15) correctSlot = true;
        else if (emotionID == m_slotIDs[15] && m_currentSlotIndex == 16) correctSlot = true;
        else if (emotionID == m_slotIDs[16] && m_currentSlotIndex == 17) correctSlot = true;
        else if (emotionID == m_slotIDs[17] && m_currentSlotIndex == 18) correctSlot = true;
        else if (emotionID == m_slotIDs[18] && m_currentSlotIndex == 19) correctSlot = true;
        else if (emotionID == m_slotIDs[19] && m_currentSlotIndex == 20) correctSlot = true;

        if (correctSlot) {
            clearTimerAt((uint32_t)&m_durationTimer, 0);
        }
    }
};