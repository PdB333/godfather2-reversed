// FUNC_NAME: PlayerStateMachine::handleStateEvent
// Function address: 0x00923280
// Handles state change requests with special handling for state 1 (always accepted)
// and state transitions that cycle through 3 sub-states (mod 3).
// When requested state equals current state, triggers a virtual update method.
// Clears global flags when transitioning to a different state.

int __thiscall PlayerStateMachine::handleStateEvent(int *this, int requestedState)
{
  int currentState;
  int newCycleIndex;
  // local struct used for update data (size 12 bytes)
  // actual structure might be defined elsewhere
  struct UpdateData {
    int field0;
    int field8;
    int fieldC; // likely padding or unused
  } updateData;

  // State 1 is always accepted (returns 1)
  if (requestedState == 1) {
    return 1;
  }

  // Get the current state from a global/static function
  currentState = FUN_00466860(); // likely getCurrentState() or similar

  if (requestedState == currentState) {
    // Same state: call virtual update method (vtable offset 0x2c)
    (*(void (**)(void))(*this + 0x2c))();
    // Prepare update data with a known global value
    updateData.field0 = DAT_01130310; // s_globalUpdateParam
    updateData.field8 = 0;
    updateData.fieldC = 0;
    FUN_00408a00(&updateData, 0); // processUpdate(&updateData, 0)
    return 0;
  }
  
  // Transition to a different state
  // For state 2 and 4, modify the cycle index (stored at offset 0x50)
  // and call a function to apply the new cycle selection
  if (requestedState == 2) {
    newCycleIndex = this[0x14] + 1; // increment cycle index
  }
  else if (requestedState == 4) {
    newCycleIndex = this[0x14] + 2; // increment by 2 (effectively decrement mod 3)
  }
  else {
    // Unhandled state (only 1,2,4 and current are valid)
    return 0;
  }
  
  // Apply the new cycle index (mod 3) – cycles through 3 sub-states
  FUN_00923190(newCycleIndex % 3); // setCycleIndex(newCycleIndex % 3)
  
  // Clear global flags after state change
  FUN_00402050(&DAT_01130270, 0); // clearFlag(&s_flag1, 0)
  FUN_00402050(&DAT_011304d8, 0); // clearFlag(&s_flag2, 0)
  
  return 0;
}