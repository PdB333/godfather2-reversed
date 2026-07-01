// FUNC_NAME: Entity::getSomeProperty
void Entity::getSomeProperty(int param_1, undefined4 param_2, undefined4 param_3, undefined4 *param_4)
{
  int iVar1;
  undefined4 *puVar2;
  int local_8 [2];
  
  if ((param_1 != 0) && (*(char *)(param_1 + 0x10) + param_1 != 0)) {
    FUN_004af8c0(local_8,0x2002);
    iVar1 = 0;
    if (local_8[0] != 0) {
      iVar1 = local_8[0];
    }
    if ((iVar1 != 0) && (iVar1 = FUN_00558d40(param_1,param_2), iVar1 != -1)) {
      FUN_00558a10(iVar1);
      puVar2 = (undefined4 *)FUN_00558b00(iVar1);
      *param_4 = *puVar2;
    }
  }
  return;
}