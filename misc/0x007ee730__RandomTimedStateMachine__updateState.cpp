// FUNC_NAME: RandomTimedStateMachine::updateState
// Address: 0x007ee730
// This function appears to be a state machine update with random timing.
// It uses a global random value table (DAT_010c2680) and a counter (DAT_012054b4).
// param_1 points to a state structure: [0] = state, [1] = type, [2] = result

undefined1 __fastcall RandomTimedStateMachine::updateState(int *stateData)
{
  int baseAddr;
  uint randomIndex;
  float threshold;
  float offset;
  
  baseAddr = DAT_0112bb50; // Global base address for timing parameters
  if (*stateData != 1) { // Check if current state is "waiting" (state 1)
    return 0; // Not in waiting state, no update
  }
  
  threshold = *(float *)(DAT_0112bb50 + 0x60); // Base threshold value at +0x60
  
  if (stateData[1] == 1) { // Type 1: uses offset at +0x64 (100 decimal)
    offset = *(float *)(DAT_0112bb50 + 100); // +0x64 offset
LAB_007ee760:
    threshold = offset + threshold; // Add offset to base threshold
  }
  else if (stateData[1] == 2) { // Type 2: uses offset at +0x68
    offset = *(float *)(DAT_0112bb50 + 0x68);
    goto LAB_007ee760;
  }
  
  randomIndex = DAT_010c2678 & DAT_012054b4; // Mask random counter with bitmask
  DAT_012054b4 = DAT_012054b4 + 1; // Increment random counter
  
  if (threshold < *(float *)(&DAT_010c2680 + randomIndex * 4)) { // Compare with random value
    return 0; // Random value exceeds threshold, stay in current state
  }
  
  // Transition to next state
  *stateData = 2; // Set state to "ready" (state 2)
  
  threshold = *(float *)(baseAddr + 0x50); // Base value for result calculation at +0x50
  if (stateData[1] == 1) {
    offset = *(float *)(baseAddr + 0x58); // +0x58 offset for type 1
  }
  else {
    if (stateData[1] != 2) goto LAB_007ee7b7; // Unknown type, skip offset
    offset = *(float *)(baseAddr + 0x5c); // +0x5c offset for type 2
  }
  threshold = offset + threshold; // Add offset to base
  
LAB_007ee7b7:
  randomIndex = DAT_010c2678 & DAT_012054b4; // Get next random value
  DAT_012054b4 = DAT_012054b4 + 1;
  
  // Calculate result: random * multiplier + base
  stateData[2] = (int)(*(float *)(&DAT_010c2680 + randomIndex * 4) * *(float *)(baseAddr + 0x54) + threshold);
  
  return 1; // State transition occurred
}