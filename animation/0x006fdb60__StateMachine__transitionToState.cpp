// FUNC_NAME: StateMachine::transitionToState
// Function address: 0x006fdb60
// Role: Handles state transitions with validation, callback, and post-transition actions for a generic state machine.
// The object has an expected previous state (mExpectedPreviousState) and a current state.
// Transition is allowed if:
//   - mExpectedPreviousState is 0 and newState is 5 (forced transition), or
//   - mExpectedPreviousState matches the provided previousState.
// After storing newState, invokes a stored callback (mCallback) with previousState, newState, and user data.
// Then performs post-transition actions based on newState (0,3,4: cleanup; 2: specific enter actions).

struct StateMachine {
    void (*mCallback)(int previousState, int newState, void* userData); // +0x00
    void* mUserData;                                                     // +0x04
    // unknown padding/fields at +0x08 to +0x14? (indices 2-5 unused locally)
    int mExpectedPreviousState;  // +0x18 (index 6)
    int mCurrentState;           // +0x1C (index 7)
    // unknown at +0x20 to +0x24 (indices 8-9)
    int mResourceID;             // +0x28 (index 10)
    char mFlags;                 // +0x2C (byte at this+0x0B, used as bitfield)
};

// Forward declarations of called global functions
extern int* gGlobalManager; // DAT_0112a9f4 (presumed singleton pointer)
void stopFocusOnResource(int resourceID);            // FUN_006fd6a0
void cleanupAfterStateExited();                      // FUN_006fd240
void resetStateMachine();                            // FUN_006fd030
bool canEnterState();                                // FUN_006fd120 (returns char, treated as bool)
void enterStateEffect();                             // FUN_006fd150

void __thiscall StateMachine::transitionToState(this, int previousState, int newState) {
    int iVar1 = this->mExpectedPreviousState;

    // Validate transition: either match expected previous state, or forced transition when expected is 0 and newState is 5
    if (iVar1 != 0) {
        if (previousState == iVar1) goto LAB_accept;
        // If expected state is set but doesn't match, reject (no transition)
        if (iVar1 != 0) {
            return; // early exit
        }
    } else {
        // Expected state is 0, only allow if newState is 5 (forced)
        if (newState != 5) {
            return;
        }
    }

LAB_accept:
    this->mCurrentState = newState;

    // Invoke the callback (if set)
    if (this->mCallback != nullptr) {
        this->mCallback(previousState, newState, this->mUserData);
    }

    // Post-transition actions based on the new state
    switch (newState) {
        case 0:
        case 3:
        case 4:
            // Release focus if resource ID matches the current focus ID
            if (this->mResourceID != -1) {
                // gGlobalManager + 0x208 likely holds the ID of the currently focused resource
                int* focusPtr = reinterpret_cast<int*>(reinterpret_cast<char*>(gGlobalManager) + 0x208);
                if (*focusPtr == this->mResourceID) {
                    stopFocusOnResource(this->mResourceID);
                }
            }
            // If a specific flag (bit 3) is set, do general cleanup
            if (this->mFlags & 8) {
                cleanupAfterStateExited();
            }
            // If we are leaving the expected previous state, reset the machine
            if (this->mExpectedPreviousState == previousState) {
                resetStateMachine();
            }
            break;

        case 2:
            // Same focus release logic
            if (this->mResourceID != -1) {
                int* focusPtr = reinterpret_cast<int*>(reinterpret_cast<char*>(gGlobalManager) + 0x208);
                if (*focusPtr == this->mResourceID) {
                    stopFocusOnResource(this->mResourceID);
                }
            }
            // If flag set and entering state is allowed, play enter effect
            if ((this->mFlags & 8) && !canEnterState()) {
                enterStateEffect();
            }
            break;
    }
}