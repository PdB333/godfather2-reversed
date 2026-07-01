// FUNC_NAME: VoipManager::updatePlayerVisibility

// Function address: 0x00967020
// Role: Updates the VoIP visibility state for a specific player, logs the status and counts of participants.

#include <cstdint>

// Forward declarations for internal functions (likely part of a debug/logging system)
// These are stubs - actual implementations would be elsewhere.
void DebugSetLogLevel(int level);
void DebugLogPop(int count);
void DebugLogPrintLine(const char* text);
void DebugLogPrintFormatted(const char* format, int arg1, int* arg2, int arg3, const char* defaultStr, const char* str1, const char* str2);

// Structure representing a participant in the VoIP system
struct VoipParticipant {
    int32_t voiceState;      // +0x10: 1 = talking, 2 = neutral, 3 = muted
    int32_t playerId;        // +0x5c: unique identifier
    // other fields...
};

// Structure representing the manager (this)
struct VoipManager {
    VoipParticipant** participants; // +0x4c: pointer to array of participant pointers
    uint32_t participantCount;      // +0x50: number of participants
    // other fields...
};

void __thiscall VoipManager::updatePlayerVisibility(int32_t playerId, char logLevel) {
    DebugSetLogLevel(0); // Set log level to silent initially

    int talkCount = 0;
    int muteCount = 0;
    int otherCount = 0;
    int visibilityType = 2; // default neutral

    // Count participants and find the matching one
    if (this->participantCount != 0) {
        VoipParticipant** pp = this->participants;
        for (uint32_t i = 0; i < this->participantCount; i++) {
            VoipParticipant* part = *pp;
            bool isMatch = (part->playerId == playerId);

            if (isMatch) {
                visibilityType = part->voiceState;
            }

            // Count by voiceState type
            switch (part->voiceState) {
                case 1: // talking
                    talkCount++;
                    break;
                case 3: // muted
                    muteCount++;
                    break;
                default: // neutral/other (2)
                    otherCount++;
                    break;
            }

            if (isMatch) {
                int countIndex = i; // zero-based index of matching participant
                DebugLogPop(countIndex);
                // Local variable callback (cleanup?) - typical pattern for custom string destructor
                if (/* some local callback non-zero */) {
                    // This likely cleans up a string that was created earlier
                }
                break;
            }
            pp++;
        }
    }

    // Determine the status string based on visibilityType
    const char* statusString = nullptr;
    switch (visibilityType) {
        case 1:
            statusString = /* PTR_LAB_00d8e0fc - likely "talking" or similar */;
            break;
        case 2:
            statusString = "neutral";
            break;
        case 3:
            statusString = /* DAT_00d8e160 - likely "muted" */;
            break;
        default:
            break;
    }
    if (statusString) {
        DebugLogPrintLine(statusString);
    }

    // Second log call with the request parameter
    DebugSetLogLevel(logLevel);
    // String variables from stack: local_30 and puStack_20 (probably player name and status string)
    // They may be custom string objects; if null, use a default empty string (DAT_0120546e)
    const char* str1 = /* local_30 */;
    const char* str2 = /* puStack_20 */;
    if (str1 == nullptr) str1 = "";
    if (str2 == nullptr) str2 = "";
    DebugLogPrintFormatted("UpdateVoIPVisibility", 0, /* &DAT_00d8cdec */, 3, "", str1, str2);
    // Cleanup: if those strings were allocated, destroy them via function pointers
}