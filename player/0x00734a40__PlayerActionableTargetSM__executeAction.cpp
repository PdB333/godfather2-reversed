// FUNC_NAME: PlayerActionableTargetSM::executeAction
// Address: 0x00734a40
// This function processes an action on a target, checking if the action applies to the player or the target,
// then applying appropriate effects (sound, visual feedback, network events).
// Uses large offsets (0x71e, 0x94a) for actor pointers, and 0x1f50 for ability state on this.
// Virtual function at vtable+0x270 determines action type (0=idle,1-4=action types).
// Cooldown timers at offset 0x9c2, 0x9c3 (as floats) gate sound triggers.

void __thiscall PlayerActionableTargetSM::executeAction(int thisPtr, int *targetInfo)
{
  int *selectedPropPtr;
  int abilityBase;
  int actionType;
  float effectValue;
  int audioHandle;
  int netMessageHash;
  int unused;

  // Check if thisPtr matches either of the two actors stored in targetInfo
  // Offset 0x71e and 0x94a are likely pointers to actors (e.g., player and target)
  // The -0x48 adjustment suggests the stored values are offsets into a larger struct?
  // Actually, the comparison is: targetInfo[0x71e] (if non-zero) gives a pointer, subtract 0x48 to get base object pointer
  // Then compare to thisPtr.
  int *playerActorPtr = targetInfo[0x71e];
  int *adjustedPlayer = (playerActorPtr != 0) ? (playerActorPtr - 0x48) : 0;

  if (adjustedPlayer != thisPtr) {
    int *targetActorPtr = targetInfo[0x94a];
    int *adjustedTarget = (targetActorPtr != 0) ? (targetActorPtr - 0x48) : 0;
    if (adjustedTarget != thisPtr) {
      // thisPtr does not match either stored actor -> apply action without sound/network
      selectedPropPtr = 0;
      int *abilityState = *(int **)(thisPtr + 0x1f50);
      if (abilityState == 0) return;
      abilityBase = *(int *)(abilityState + 0x1c);
      if (abilityBase == 0) return;
      if (abilityBase == 0x3c) return; // 0x3c = 60, likely special sentinel

      actionType = (**(code **)(*targetInfo + 0x270))(); // virtual function on targetInfo
      switch(actionType) {
        case 1:
          selectedPropPtr = *(int **)(abilityBase + 100); // +0x64
          break;
        case 2:
          selectedPropPtr = *(int **)(abilityBase + 0x68); // +0x68
          break;
        case 3:
          selectedPropPtr = *(int **)(abilityBase + 0x6c); // +0x6c
          break;
        case 4:
          selectedPropPtr = *(int **)(abilityBase + 0x70); // +0x70
          break;
        default:
          // case 0? Not handled in this branch, might be invalid
          break;
      }
      effectValue = (float)FUN_0078a5b0(selectedPropPtr); // likely returns a float value
      FUN_0078b4b0((float)effectValue, 0, 1); // apply effect with mode 0,1
      return;
    }
  }

  // thisPtr matches one of the stored actors -> apply action with sound/network
  selectedPropPtr = 0;
  int *abilityState = *(int **)(thisPtr + 0x1f50);
  if (abilityState != 0) {
    abilityBase = *(int *)(abilityState + 0x1c);
    if (abilityBase != 0 && abilityBase != 0x3c) {
      actionType = (**(code **)(*targetInfo + 0x270))();
      switch(actionType) {
        case 0:
          selectedPropPtr = *(int **)(abilityBase + 0x74); // +0x74
          break;
        case 1:
          // Check cooldown timer at targetInfo[0x9c2] (float)
          if (*(float *)&(targetInfo[0x9c2]) <= 0.0f) {
            selectedPropPtr = *(int **)(abilityBase + 0x78); // +0x78
            FUN_0078b270(6); // play sound? 6 might be a sound ID
            if (FUN_00732380() != 0) { // some condition check
              audioHandle = FUN_006fbc40(0, 0); // get audio handler
              FUN_007f96a0(0x88265e7b, 100, audioHandle, 0); // post event with hash
              FUN_006fbc70(); // release handler
              // Get network interface and send message
              targetInfo = (int *)FUN_006ad7f0(targetInfo); // likely get network session
              (**(code **)(*targetInfo + 0x28))(0xfa04d879, 0, 0xffffffff, 0); // send network message
              if (FUN_0078a7d0() != 0) { // check if online/multiplayer
                audioHandle = FUN_006fbc40(0, 0);
                FUN_007f96a0(0x339a2d79, 100, audioHandle, 0);
                FUN_006fbc70();
              }
            }
          }
          break;
        case 2:
          // Check cooldown timer at targetInfo[0x9c3] (float)
          if (*(float *)&(targetInfo[0x9c3]) <= 0.0f) {
            selectedPropPtr = *(int **)(abilityBase + 0x7c); // +0x7c
            FUN_0078b270(6);
            if (FUN_00732380() != 0) {
              audioHandle = FUN_006fbc40(0, 0);
              FUN_007f96a0(0x88265e7b, 100, audioHandle, 0);
              FUN_006fbc70();
              targetInfo = (int *)FUN_006ad7f0(targetInfo);
              (**(code **)(*targetInfo + 0x28))(0xfa04d879, 0, 0xffffffff, 0);
              if (FUN_0078a7d0() != 0) {
                audioHandle = FUN_006fbc40(0, 0);
                FUN_007f96a0(0x339a2d79, 100, audioHandle, 0);
                FUN_006fbc70();
              }
            }
          }
          break;
        case 3:
          selectedPropPtr = *(int **)(abilityBase + 0x80); // +0x80
          break;
        case 4:
          selectedPropPtr = *(int **)(abilityBase + 0x84); // +0x84
          break;
        default:
          break;
      }
      effectValue = (float)FUN_0078a5b0(selectedPropPtr);
      FUN_0078b4b0((float)effectValue, 1, 1); // apply effect with mode 1,1

      // Always post a final audio event (hash 0)
      audioHandle = FUN_006fbc40(0, 0);
      FUN_007f96a0(0, 0, audioHandle, 0);
      FUN_006fbc70();
    }
  }
  return;
}