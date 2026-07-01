// FUNC_NAME: SimNpc::getCurrentAction
int __fastcall SimNpc::getCurrentAction(int thisPtr)
{
  char cVar1;
  int iVar2;
  int uVar3;
  
  // Check if action state is 0 (idle) or 0x48 (some specific state)
  if (((*(int *)(thisPtr + 0x9c) == 0) || (*(int *)(thisPtr + 0x9c) == 0x48)) ||
     (cVar1 = FUN_007f4800(), cVar1 == '\0')) {
    // If idle or special state, get the base action
    uVar3 = FUN_007914e0();
    iVar2 = FUN_008c74d0(uVar3);
    return iVar2;
  }
  
  // If action state is non-zero and not 0x48
  if (*(int *)(thisPtr + 0x9c) == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)(thisPtr + 0x9c) + -0x48;  // Subtract 0x48 to get base offset
  }
  
  // Check if there's a current action at offset +0x1ed8
  if (*(int *)(iVar2 + 0x1ed8) != 0) {
    return *(int *)(iVar2 + 0x1ed8) + -0x48;  // Return action minus 0x48 offset
  }
  
  return 0;  // No current action
}