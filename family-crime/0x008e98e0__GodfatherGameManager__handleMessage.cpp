// FUNC_NAME: GodfatherGameManager::handleMessage
void __thiscall GodfatherGameManager::handleMessage(int this, int *param_2)
{
  int iVar1;
  uint uVar2;
  
  iVar1 = *param_2;
  if ((iVar1 == DAT_0120e93c) || (iVar1 == DAT_012067dc)) {
    FUN_0046efc0(param_2);
    return;
  }
  if (iVar1 == DAT_0112a628) {
    if ((*(int *)(this + 0x144) != 0) &&
       (*(int *)(*(int *)(param_2[1] + 4) + 0x38) == *(int *)(this + 0x144))) {
      FUN_008e97a0(*(undefined4 *)(*(int *)(param_2[1] + 4) + 0xd4));
      iVar1 = FUN_006b1980();
      uVar2 = 0;
      if (*(int *)(iVar1 + 4) != 0) {
        do {
          FUN_008e2900(*(undefined4 *)(this + 0x144));
          uVar2 = uVar2 + 1;
        } while (uVar2 < *(uint *)(iVar1 + 4));
      }
    }
  }
  else if (iVar1 == DAT_0112a5e0) {
    if (((*(int *)(this + 0x144) != 0) &&
        (*(int *)(*(int *)(param_2[1] + 4) + 0x38) == *(int *)(this + 0x144))) &&
       (*(int *)(this + 0x14c) != 0)) {
      FUN_00402050(this + 0x14c,0);
      return;
    }
  }
  else {
    iVar1 = (**(code **)(*(int *)(this + -0x3c) + 0x15c))();
    if (iVar1 != 0) {
      (**(code **)(*(int *)(iVar1 + 0x3c) + 4))(param_2);
      return;
    }
  }
  return;
}