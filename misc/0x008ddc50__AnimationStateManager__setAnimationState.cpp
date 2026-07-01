// FUNC_NAME: AnimationStateManager::setAnimationState
void __thiscall AnimationStateManager::setAnimationState(int this, uint animationId, uint stateIndex)
{
  uint *stateArrayEntry;
  
  if ((animationId < 0x19) && (stateIndex < 4)) {
    // Access state array at offset +0x24, each entry is 0xC bytes
    stateArrayEntry = (uint *)(*(int *)(this + 0x24) + animationId * 0xc);
    *stateArrayEntry = stateIndex;
    // Check if the state is already set to a non-zero value or 0x48 (likely a special state)
    if ((stateArrayEntry[1] != 0) && (stateArrayEntry[1] != 0x48)) {
      if (stateArrayEntry[1] != 0) {
        FUN_008dd2c0(stateIndex); // Likely updateAnimationState
        return;
      }
      FUN_008dd2c0(stateIndex); // Likely updateAnimationState
    }
  }
  return;
}