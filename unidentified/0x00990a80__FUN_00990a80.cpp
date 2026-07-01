// FUNC_NAME: SomeManager::broadcastToListeners
void __thiscall SomeManager::broadcastToListeners(int this, undefined4 *param_2)
{
  int iVar1;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  
  for (iVar1 = *(int *)(this + 0x60); iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
    if (*(int *)(iVar1 + 0x38) != 0) {
      FUN_004df780(&local_50);
      local_50 = *param_2;
      uStack_4c = param_2[1];
      uStack_48 = param_2[2];
      uStack_44 = param_2[3];
      local_40 = param_2[4];
      uStack_3c = param_2[5];
      uStack_38 = param_2[6];
      uStack_34 = param_2[7];
      local_30 = param_2[8];
      uStack_2c = param_2[9];
      uStack_28 = param_2[10];
      uStack_24 = param_2[0xb];
      FUN_004df720(&local_50);
    }
    if (*(int *)(iVar1 + 0x3c) != 0) {
      FUN_004df780(&local_50);
      local_50 = *param_2;
      uStack_4c = param_2[1];
      uStack_48 = param_2[2];
      uStack_44 = param_2[3];
      local_40 = param_2[4];
      uStack_3c = param_2[5];
      uStack_38 = param_2[6];
      uStack_34 = param_2[7];
      local_30 = param_2[8];
      uStack_2c = param_2[9];
      uStack_28 = param_2[10];
      uStack_24 = param_2[0xb];
      FUN_004df720(&local_50);
    }
  }
  return;
}