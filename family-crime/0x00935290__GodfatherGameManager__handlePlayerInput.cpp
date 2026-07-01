// FUNC_NAME: GodfatherGameManager::handlePlayerInput
void GodfatherGameManager::handlePlayerInput(undefined4 param_1, int param_2, short param_3, undefined4 param_4)
{
  int *piVar1;
  char cVar2;
  int iVar3;
  undefined4 unaff_EBP;
  int iVar4;
  char unaff_SI;
  char unaff_retaddr;
  
  if (DAT_012234b8 == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = DAT_012234b8 + -0xc;
  }
  iVar4 = (int)param_3;
  FUN_008a18f0((char)param_1 + 1,param_2 + 1,iVar4 + 1);
  piVar1 = *(int **)(iVar3 + 0x234); // +0x234: inputDeviceManager
  iVar3 = (**(code **)(*piVar1 + 4))(param_4); // vtable+4: getInputState
  iVar3 = iVar3 + 0x80; // offset to controller state
  cVar2 = (**(code **)(*piVar1 + 0xc))(iVar3,(int)unaff_retaddr,param_1,iVar4); // vtable+0xc: isButtonPressed
  if (cVar2 != '\0') {
    cVar2 = (**(code **)(*piVar1 + 8))(iVar3,(int)unaff_SI,unaff_EBP,iVar4); // vtable+8: isButtonHeld
    if (cVar2 != '\0') {
      FUN_008a1910(iVar3); // handleAction
      FUN_008a1940(); // playSound
      iVar3 = DAT_01129928; // gameManager instance
      DAT_00e5672c = 0xc; // set game state
      *(undefined4 *)(DAT_01129928 + 0x60) = 0; // +0x60: clear some flag
      if ((DAT_01130590 & 1) == 0) {
        FUN_005c0d50(iVar3 + 0x14,&LAB_00931e00,0); // schedule event
        DAT_01130590 = DAT_01130590 | 1;
      }
      return;
    }
  }
  DAT_01130590 = DAT_01130590 | 0x40;
  FUN_00933e70(); // handleInputFailure
  return;
}