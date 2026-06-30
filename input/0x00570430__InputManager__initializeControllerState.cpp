// FUNC_NAME: InputManager::initializeControllerState
void __thiscall InputManager::initializeControllerState(int param_1, int param_2)
{
  undefined4 in_EAX;
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int unaff_ESI;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  // Store the controller state pointer at +0xB8
  *(undefined4 *)(param_1 + 0xb8) = in_EAX;
  
  // If the controller data buffer hasn't been allocated yet (+0xB4)
  if (*(int *)(param_1 + 0xb4) == 0) {
    local_1c = 0;
    local_18 = 0;
    local_14 = 0;
    // Allocate memory for controller data based on number of controllers (+0xB0)
    uVar1 = (**(code **)*DAT_0120556c)((int)*(short *)(param_1 + 0xb0), &local_1c);
    *(undefined4 *)(param_1 + 0xb4) = uVar1;
  }
  
  // Initialize the controller data buffer to 0xFF (unused state)
  iVar2 = 0;
  if (0 < *(short *)(param_1 + 0xb0)) {
    do {
      *(undefined1 *)(iVar2 + *(int *)(param_1 + 0xb4)) = 0xff;
      iVar2 = iVar2 + 1;
    } while (iVar2 < *(short *)(param_1 + 0xb0));
  }
  
  // Initialize each controller slot (0x40 bytes each)
  uVar1 = DAT_00e2b1a4;
  if (0 < unaff_ESI) {
    iVar4 = 0;
    iVar2 = unaff_ESI;
    do {
      puVar3 = (undefined4 *)(*(int *)(param_1 + 0xb8) + iVar4);
      *puVar3 = uVar1;           // +0x00: initial value
      puVar3[1] = 0;             // +0x04: zero
      puVar3[2] = 0;             // +0x08: zero
      puVar3[3] = 0;             // +0x0C: zero
      puVar3[4] = 0;             // +0x10: zero
      puVar3[5] = uVar1;         // +0x14: initial value
      puVar3[6] = 0;             // +0x18: zero
      puVar3[7] = 0;             // +0x1C: zero
      puVar3[8] = 0;             // +0x20: zero
      puVar3[9] = 0;             // +0x24: zero
      puVar3[10] = uVar1;        // +0x28: initial value
      puVar3[0xb] = 0;           // +0x2C: zero
      iVar4 = iVar4 + 0x40;      // Advance to next controller slot
      iVar2 = iVar2 + -1;
      puVar3[0xc] = 0;           // +0x30: zero
      puVar3[0xd] = 0;           // +0x34: zero
      puVar3[0xe] = 0;           // +0x38: zero
      puVar3[0xf] = uVar1;       // +0x3C: initial value
    } while (iVar2 != 0);
  }
  
  // If this is a local game (param_2+0x38 == 1) and we have the right number of controllers
  if ((*(int *)(param_2 + 0x38) == 1) && (unaff_ESI == *(short *)(param_1 + 0xb0))) {
    // Map controllers sequentially (local multiplayer)
    iVar2 = 0;
    if (0 < unaff_ESI) {
      do {
        *(char *)(iVar2 + *(int *)(param_1 + 0xb4)) = (char)iVar2;
        iVar2 = iVar2 + 1;
      } while (iVar2 < unaff_ESI);
      return;
    }
  }
  else {
    // For network/other modes, use a different mapping function
    FUN_005703d0(param_2);
  }
  return;
}