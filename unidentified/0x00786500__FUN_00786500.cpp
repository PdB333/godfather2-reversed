// FUNC_NAME: SomeManager::processPendingActions
void __fastcall SomeManager::processPendingActions(int this)
{
  int iVar1;
  uint uVar2;
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = DAT_01205228 + _DAT_00d5780c;
  uVar2 = 0;
  local_8 = 0;
  if (*(int *)(this + 0x1a3c) != 0) {
    do {
      iVar1 = FUN_00788550(local_c);
      if (iVar1 != 0) {
        local_c = *(float *)(iVar1 + 8);
        local_8 = iVar1;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(this + 0x1a3c));
  }
  FUN_00788c10(local_8);
  return;
}