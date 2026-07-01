// FUNC_NAME: PlayerSM::handleAction
void __thiscall PlayerSM::handleAction(int thisPtr, int param2, int param3)
{
  int actionType;
  int prevActionType;
  undefined4 soundId;
  
  // Retrieve the action type from the action slot at index param3
  // +0x1c: action type array offset, each slot is 0x24 bytes
  prevActionType = *(int *)(thisPtr + 0x1c + param3 * 0x24);
  
  // Clear the action slot at index param2
  // +0x18: action slot array offset
  FUN_0090a490(thisPtr + 0x18 + param2 * 0x24);
  
  // Store the previous action type into the new slot
  *(int *)(thisPtr + param3 * 0x24 + 0x1c) = prevActionType;
  
  // Update state machine
  FUN_0090a9f0();
  
  // Check if we should process the action
  actionType = FUN_0090a5a0();
  if (actionType == 0) goto LAB_0090b3d4;
  
  // Play sound based on action type
  FUN_00791670(prevActionType, 1);
  
  if (prevActionType == 4) {
    // Action type 4: play "take cover" sound
    FUN_007e7df0(0x36);
    soundId = 0xd3d2af26;
LAB_0090b3a9:
    FUN_00894c90(soundId);
  }
  else if (prevActionType == 5) {
    // Action type 5: play "exit cover" sound
    FUN_007e7df0(0x37);
    soundId = 0x80e1bade;
    goto LAB_0090b3a9;
  }
  
  // Handle additional action processing
  actionType = FUN_00791300();
  if (actionType != 0) {
    FUN_00737940(3, 0);
    FUN_0090a500(actionType);
  }
  
LAB_0090b3d4:
  // Finalize state machine update
  FUN_009bc210();
  return;
}