// FUNC_NAME: GangsterNpcRequester::requestGangster
void __thiscall FUN_008c8d00(int this,int param_2)

{
  int iVar1;
  int iVar2;
  
  *(int *)(this + 0x18) = param_2;
  FUN_00790d30(param_2);
  if (*(int *)(this + 0x10) != 0) {
    if (*(int *)(*(int *)(this + 0x10) + 0x58) == param_2) {
      FUN_008feb40();
    }
    else {
      FUN_008febb0();
    }
  }
  iVar2 = FUN_006b0ee0(param_2);
  iVar1 = *(int *)(iVar2 + 0xfc);
  if (*(int *)(iVar2 + 0x40) != *(int *)(*(int *)(this + 0xc) + 0x54)) {
    FUN_008c8cb0();
    return;
  }
  FUN_006b4730(*(undefined4 *)(this + 8),0);
  if (iVar1 != 0) {
    FUN_006bf5b0(*(undefined4 *)(this + 8));
    FUN_008bd860(this,2,param_2,0);
    return;
  }
  if (*(int *)(this + 4) != 1) {
    *(undefined4 *)(this + 0x14) = 0;
    FUN_008c83b0(*(int *)(this + 4),1,0);
    *(undefined4 *)(this + 4) = 1;
  }
  return;
}