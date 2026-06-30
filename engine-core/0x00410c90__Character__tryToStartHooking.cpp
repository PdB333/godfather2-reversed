// FUNC_NAME: Character::tryToStartHooking
// Address: 0x00410c90
// Identified role: This function checks if the character can transition to a "hooking" state (0x12),
// which likely initiates an interaction such as grabbing, taking cover, or using an object.
// It requires the primary action to be idle/not active and the secondary action to be active.

#include <cstdint>

// Forward declaration of the helper function that checks if an action state is currently active.
bool isActionActive(uint8_t actionState);

class Character {
public:
    // Offsets based on decompilation:
    // +0x544 : float m_velocityX
    // +0x548 : float m_velocityY
    // +0x54c : float m_velocityZ
    // +0x550 : int32_t m_flags          // e.g., grounded flag or bitfield
    // +0x564 : uint8_t m_primaryAction  // current primary action state
    // +0x565 : uint8_t m_secondaryAction// current secondary action state
    // +0x568 : uint8_t m_hookingState   // state to be set for hooking/interaction
    // +0x56c : int32_t m_hookingTimer   // associated timer/counter

    void tryToStartHooking();

    // Other members would be declared here, but we only need the relevant ones.
    // For clarity in this reconstruction, we use explicit offset access via helper macros.

private:
    // Inline accessors for the relevant offsets (using this pointer)
    float& velocityX()       { return *(float*)((uint8_t*)this + 0x544); }
    float& velocityY()       { return *(float*)((uint8_t*)this + 0x548); }
    float& velocityZ()       { return *(float*)((uint8_t*)this + 0x54c); }
    int32_t& flags()         { return *(int32_t*)((uint8_t*)this + 0x550); }
    uint8_t& primaryAction() { return *(uint8_t*)((uint8_t*)this + 0x564); }
    uint8_t& secondaryAction(){ return *(uint8_t*)((uint8_t*)this + 0x565); }
    uint8_t& hookingState()  { return *(uint8_t*)((uint8_t*)this + 0x568); }
    int32_t& hookingTimer()  { return *(int32_t*)((uint8_t*)this + 0x56c); }
};

void Character::tryToStartHooking() {
    // State constant 0x12 likely represents "hooking" or "interacting".
    const uint8_t STATE_HOOKING = 0x12;

    // If already in hooking state, do nothing.
    if (hookingState() == STATE_HOOKING) {
        return;
    }

    // Condition to allow hooking transition:
    // - Primary action is already hooking, OR
    // - Primary action is not active AND the character is completely stationary.
    if (primaryAction() == STATE_HOOKING ||
        (!isActionActive(primaryAction()) &&
         velocityX() == 0.0f && velocityY() == 0.0f && velocityZ() == 0.0f &&
         flags() == 0)) {
        // Now check secondary action.
        if (secondaryAction() == STATE_HOOKING) {
            return;
        }
        // Secondary action must be active to proceed.
        if (!isActionActive(secondaryAction())) {
            return;
        }
        // Transition to hooking state.
        hookingState() = STATE_HOOKING;
        hookingTimer() = 0;
    }
}

// Note: The helper function isActionActive is defined elsewhere (address 0x00410b90).
// It checks whether the given action state byte represents an active, ongoing action.
// It returns true if the action is active, false otherwise. Its implementation is not shown here.