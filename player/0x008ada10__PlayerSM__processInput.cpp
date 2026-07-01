// FUNC_NAME: PlayerSM::processInput
void __thiscall PlayerSM::processInput(int thisPtr, int *inputData, int param_3)
{
  int *piVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  bool bVar6;
  undefined4 uStack_1c;
  int iStack_18;
  undefined1 uStack_14;
  undefined **local_10;
  int local_c;
  int local_8;
  int local_4;
  
  piVar1 = inputData;
  // Check if input processing is enabled (bit 4 of flags at +0x7c)
  if ((*(uint *)(thisPtr + 0x7c) >> 4 & 1) == 0) {
    return;
  }
  
  // Get current state machine state (+0x60)
  iVar3 = *(int *)(thisPtr + 0x60);
  if ((iVar3 == 0) || (local_8 = iVar3, *(int *)(iVar3 + 8) == 0)) {
    local_8 = 0;
  }
  
  local_c = 0;
  local_10 = &PTR_FUN_00d79c8c; // State iterator function table
  local_4 = 0;
  if (local_8 != 0) {
    local_4 = iVar3;
  }
  
  do {
    if ((local_c == 0) && (local_8 == 0)) {
      return;
    }
    
    // Get current state object
    iVar3 = (*(code *)*local_10)();
    
    // Check if state is active (bit 0 of flags at +0x30)
    if ((*(byte *)(iVar3 + 0x30) & 1) != 0) {
      // Get input device data
      uVar4 = (**(code **)(*piVar1 + 4))();
      uVar5 = FUN_004bb600(iVar3); // Get state's input handler
      cVar2 = FUN_00411fd0(uVar5, uVar4); // Compare input handler with device data
      
      if (cVar2 != '\0') {
        iVar3 = (*(code *)*local_10)();
        if (iVar3 == 0) {
          return;
        }
        
        bVar6 = param_3 == 0;
        iVar3 = iVar3 + 8;
        FUN_008ab7d0(&inputData, iVar3); // Process input for this state
        
        if (bVar6 == (bool)(char)inputData[1]) {
          return;
        }
        
        uStack_14 = 0;
        if (bVar6) {
          uStack_1c = DAT_0112edf4; // "INPUT_ACCEPTED" string
        }
        else {
          uStack_1c = DAT_0112ef7c; // "INPUT_REJECTED" string
        }
        iStack_18 = iVar3;
        FUN_00408a00(&uStack_1c, 0); // Log input result
        FUN_008ab7d0(&inputData, iVar3);
        *(bool *)(inputData + 1) = bVar6;
        return;
      }
    }
    (*(code *)local_10[1])(); // Advance to next state
  } while(true);
}