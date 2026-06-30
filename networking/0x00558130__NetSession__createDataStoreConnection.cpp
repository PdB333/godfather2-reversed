// FUNC_NAME: NetSession::createDataStoreConnection
int NetSession::createDataStoreConnection(int param_1, int param_2, undefined4 *param_3)
{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  uint local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_20 = 2;
  local_1c = 0x10;
  local_18 = 0;
  iVar1 = FUN_009c8ed0(0x2c,&local_20);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_005582d0();
  }
  uVar4 = param_3[1];
  uVar3 = uVar4 & 0xc0000000;
  if (uVar3 == 0) {
    uVar4 = *(uint *)(*(int *)(DAT_01223480 + 0x54) + 0x34 + (uVar4 & 0x1f) * 4);
  }
  else if (uVar3 == 0x40000000) {
    uVar4 = *(uint *)(uVar4 * 4 + 4) | 1;
  }
  else if (uVar3 == 0xc0000000) {
    uVar4 = *(uint *)(uVar4 * 4 + 0x50) | 1;
  }
  else {
    uVar4 = 0xffffffff;
  }
  uVar3 = FUN_0043b490();
  local_14 = (uVar3 & 0xfff) << 0x10 | param_3[1] & 0x1f | 0x3e0;
  local_c = 0xffffffff;
  local_8 = 0;
  local_4 = 0;
  local_10 = uVar4;
  FUN_00558020(iVar1,*param_3,&local_14);
  iVar5 = *(int *)(*(int *)(iVar1 + 4) + 4);
  if (*(int *)(iVar1 + 0x1c) == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)(*(int *)(iVar1 + 0x1c) + 0x10);
  }
  if (iVar2 != 0) {
    iVar2 = (**(code **)(*(int *)(iVar2 + 0x10) + 4))();
    iVar5 = iVar5 + iVar2;
  }
  if (iVar5 == 0) {
    FUN_00558360();
    FUN_009c8eb0(iVar1);
    iVar1 = 0;
  }
  return iVar1;
}