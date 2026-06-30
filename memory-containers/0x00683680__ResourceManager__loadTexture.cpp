// FUNC_NAME: ResourceManager::loadTexture
undefined4 FUN_00683680(undefined4 param_1, undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = 2;
  local_8 = 0x10;
  local_4 = 0;
  iVar1 = FUN_0043b980(0x390, &local_c, param_2);
  if (iVar1 != 0) {
    uVar2 = FUN_009c5140(param_1, 0x4000, 3, 0x46);
    return uVar2;
  }
  return 0;
}