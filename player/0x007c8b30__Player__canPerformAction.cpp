// FUNC_NAME: Player::canPerformAction
undefined1 __fastcall Player::canPerformAction(int thisPtr)
{
  int iVar1;
  int iVar2;
  char cVar3;
  undefined1 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  // Check if game time is past a certain threshold and if a specific flag is not set
  if ((DAT_00e52f74 < *(uint *)(thisPtr + 0xd0)) &&
     ((*(uint *)(*(int *)(thisPtr + 0x58) + 0x249c) >> 0x14 & 1) == 0)) {
    return 1;
  }
  
  // Check if a specific action is allowed (e.g., using a weapon)
  uVar5 = FUN_00798f50(0x41); // Get some game state
  cVar3 = FUN_0079e970(uVar5); // Check if action is valid
  if ((cVar3 != '\0') && (*(float *)(thisPtr + 0x30) != _DAT_00d577a0)) {
    uVar6 = 0x8000; // Some flag
    uVar5 = (**(code **)(*(int *)(*(int *)(thisPtr + 0x58) + 0x1f30) + 8))(0x8000); // Get some object
    FUN_0040faf0(uVar5, uVar6); // Perform action
    return 1;
  }
  
  // Check various flags and conditions
  if ((*(uint *)(thisPtr + 0x128) >> 0xb & 1) == 0) {
    iVar2 = *(int *)(thisPtr + 0x58);
    if (((*(uint *)(iVar2 + 0x8e0) >> 0x10 & 1) == 0) &&
       ((*(uint *)(iVar2 + 0x249c) >> 0x15 & 1) == 0)) {
      if ((*(uint *)(iVar2 + 0x8e0) >> 9 & 1) == 0) {
        cVar3 = FUN_00690210(0x1c); // Check some condition
        if (cVar3 == '\0') {
          return 0;
        }
      }
      else {
        if (*(int *)(iVar2 + 0x31a8) == 0) {
          return 0;
        }
        iVar1 = *(int *)(iVar2 + 0x31a8) + -0x48;
        if (iVar1 == 0) {
          return 0;
        }
        cVar3 = FUN_00690150(0x19); // Check another condition
        if (cVar3 != '\0') {
          uVar4 = FUN_007c6ee0(iVar1, iVar2); // Perform specific action
          return uVar4;
        }
      }
    }
  }
  return 1;
}