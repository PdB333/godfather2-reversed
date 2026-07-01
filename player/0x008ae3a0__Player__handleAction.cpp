// FUNC_NAME: Player::handleAction
void __thiscall Player::handleAction(int this, int actionData)
{
  char cVar1;
  int iVar2;
  int iVar3;
  
  if (*(int *)(this + 0x60) != 0) {
    if ((*(int *)(actionData + 0x10) != -1) && (*(int *)(actionData + 0x14) != -1)) {
      iVar2 = FUN_004baf90(*(int *)(actionData + 0x10));
      iVar3 = FUN_004baf90(*(undefined4 *)(actionData + 0x14));
      if ((iVar2 != 0) && ((iVar3 != 0 && (*(int *)(iVar2 + 8) == *(int *)(iVar3 + 8))))) {
        *(undefined4 *)(actionData + 0xc) = *(undefined4 *)(this + 300);
      }
    }
    cVar1 = FUN_00481620();
    if ((cVar1 == '\\0') && (*(int *)(this + 0xd8) != 4)) {
      FUN_004bb790(actionData);
      FUN_008a8d70();
      return;
    }
    FUN_008ac8f0(actionData);
  }
  return;
}