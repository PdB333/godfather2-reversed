// FUNC_NAME: StateMachine::updateCurrentState
// Function address: 0x004184b0
// Purpose: Updates the current state data's timing, resetting accumulator when game time advances.
//          Marks state data and owning state machine as dirty.
//          If this state data is the globally active one, calls a callback with the new time.

// Structure definitions with field offsets:
// class StateMachine {
//     /* +0x00 */ void* vtable; // actual size not needed
//     /* +0x04 */ StateData* mCurrentState;  // pointer to the current state data
//     /* +0x0c */ uint8_t mDirty;            // flag indicating machine needs update
// };
// class StateData {
//     /* +0x10 */ int32_t mLastUpdateTime;   // last game time this state was updated
//     /* +0x50 */ int32_t mAccumulator;      // accumulated time for this state
//     /* +0x1b8 */ uint8_t mUpdateFlag;      // flag indicating state data was modified
// };

// Globals:
// extern int32_t gCurrentTime;         // DAT_01205440
// extern StateData* gActiveStateData;  // DAT_012058e8

// External function:
// void onStateTimeUpdate(int32_t newTime); // FUN_0060a460

void __fastcall StateMachine::updateCurrentState(StateMachine* thisPtr) // param_1 in ecx
{
    StateData* stateData = *(StateData**)(thisPtr + 4); // read mCurrentState from this+0x04
    int32_t currentTime = gCurrentTime;                 // global game time
    bool timeAdvanced = (currentTime != stateData->mLastUpdateTime); // check if time changed

    stateData->mUpdateFlag = 1;                         // mark state data as updated (offset +0x1b8)

    if (timeAdvanced) {
        stateData->mLastUpdateTime = currentTime;       // update stored time (offset +0x10)
        stateData->mAccumulator = 0;                   // reset accumulator (offset +0x50)
        if (gActiveStateData == stateData) {
            onStateTimeUpdate(currentTime);            // notify active state of new time
        }
    }

    thisPtr->mDirty = 1;                                // mark state machine as dirty (offset +0x0c)
}