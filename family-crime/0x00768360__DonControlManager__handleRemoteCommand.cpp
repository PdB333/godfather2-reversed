// FUNC_NAME: DonControlManager::handleRemoteCommand
#include <cstdint>

// Forward declarations for callees
bool handleDonCommandToggleCrew(uint8_t flag);
void handleDonCommandQuickSend();
void handleDonCommandBeginTimedAction();
void handleDonCommandCancelAction();
int32_t getRemainingTime(int32_t param);
bool defaultHandler(int32_t arg2, int32_t arg3, int32_t arg4, int32_t commandId, int32_t arg6);

// Message IDs (likely from Godfather map commands)
constexpr uint32_t kCommandToggleCrew = 0x23;    // Toggle crew aggression
constexpr uint32_t kCommandQuickSend = 0x24;     // Quick-send family members
constexpr uint32_t kCommandTimedAction = 0x25;   // Start timed action (e.g., hit)
constexpr uint32_t kCommandCancelAction = 0x26;   // Cancel current timed action

// DonControlManager implementation
int32_t __thiscall DonControlManager::handleRemoteCommand(int32_t arg2, int32_t arg3, int32_t arg4, int32_t commandId, int32_t arg6) {
    switch (commandId) {
        case kCommandToggleCrew: {
            // +0x5c: pointer to some global object (likely simulation or player state)
            // +0x21dc: offset within that global to a structure for crew-related data
            // +0x88: byte flag indicating crew AI state
            uint8_t* crewFlags = (uint8_t*)(*(this + 0x5c) + 0x21dc) + 0x88;
            bool isAggressive = (*crewFlags) & 1;
            handleDonCommandToggleCrew(isAggressive);
            return 1;
        }
        case kCommandQuickSend:
            handleDonCommandQuickSend();
            return 1;
        case kCommandTimedAction:
            // Falls through to post-switch logic
            break;
        case kCommandCancelAction:
            handleDonCommandCancelAction();
            return 1;
        default:
            return defaultHandler(arg2, arg3, arg4, commandId, arg6);
    }

    // For kCommandTimedAction (0x25)
    handleDonCommandBeginTimedAction();

    // +0x21b8: pointer to a timed event or family job structure
    int32_t* timedEventPtr = *(int32_t**)(*(this + 0x5c) + 0x21b8);
    if (timedEventPtr == nullptr) {
        // No active event → set a default cooldown of 1000 ms from current time
        // +0x70: timestamp for next allowed action
        *(this + 0x70) = arg2 + 1000;
        return 1;
    }

    // There is an active timed event; get its remaining duration
    int32_t remainingTime = getRemainingTime(*(timedEventPtr + 0x60));
    // Update the cooldown to current time + remaining
    *(this + 0x70) = remainingTime + arg2;
    return 1;
}