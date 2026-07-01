// Xbox PDB: EARS_Apt_UIPopup_Move
// FUNC_NAME: UIList::UpdateSelectedOption
// Address: 0x00982100
// Updates the current selection within the active option group, wrapping if necessary.
// param_1: this pointer to UIList
// param_2: direction delta (+1 for down, -1 for up)

void __thiscall UIList::UpdateSelectedOption(int this, int direction)
{
  // Get pointer to the currently active option group from the array at +0x4c, indexed by +0x6c
  int optionGroupPtr = *(int *)(this + 0x4c + *(int *)(this + 0x6c) * 4);
  // Number of options in this group (at +0x04 of the group)
  uint numOptions = *(uint *)(optionGroupPtr + 4);
  
  if (numOptions > 1) {
    // Compute new selection index with wrap-around: (numOptions + direction + currentSelection) % numOptions
    uint newSelection = (numOptions + direction + *(int *)(optionGroupPtr + 8)) % numOptions;
    // Store new selection both in this object (+0x70) and in the group (+0x08)
    *(uint *)(this + 0x70) = newSelection;
    *(uint *)(optionGroupPtr + 8) = newSelection;
    
    // Log the update event
    FUN_005a04a0("UpdateSelectedOption", 0, &DAT_00d90628);
    
    // Build a notification struct (likely a string/message) from global data
    int localStruct[3]; // at local_c, local_8, local_4
    localStruct[0] = DAT_01130228; // 4 bytes
    localStruct[1] = 0;             // 4 bytes
    *(byte *)&localStruct[2] = 0;   // 1 byte
    FUN_00408a00(localStruct, 0);
    return;
  }
  
  // When only one or zero options, send a different notification
  int localStruct[3];
  localStruct[0] = DAT_01130410;
  localStruct[1] = 0;
  *(byte *)&localStruct[2] = 0;
  FUN_00408a00(localStruct, 0);
  
  return;
}