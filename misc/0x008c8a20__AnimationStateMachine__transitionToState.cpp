// FUNC_NAME: AnimationStateMachine::transitionToState
void __thiscall AnimationStateMachine::transitionToState(int thisPtr, int newState, float blendTime)
{
  float fVar1;
  
  // Only transition if the state actually changes
  if (*(int *)(thisPtr + 4) != newState) {
    // Special handling for state 6 (likely a specific animation state like "death" or "knockdown")
    if (newState == 6) {
      // +0x0C: pointer to animation data/character data
      // +0x17C: some animation speed multiplier or time scale
      fVar1 = *(float *)(*(int *)(thisPtr + 0xc) + 0x17c);
      if (0.0 < fVar1) {
        // +0x14: blend duration or transition time
        // Scale the blend time by the animation speed multiplier
        *(float *)(thisPtr + 0x14) = fVar1 * *(float *)(thisPtr + 0x14);
      }
    }
    // If blendTime is non-negative, override the blend duration
    if (0.0 <= blendTime) {
      *(float *)(thisPtr + 0x14) = blendTime;
    }
    // Call the actual state transition function with the final blend time
    FUN_008c83b0(*(int *)(thisPtr + 4), newState, *(undefined4 *)(thisPtr + 0x14));
    // Update the current state
    *(int *)(thisPtr + 4) = newState;
  }
  return;
}