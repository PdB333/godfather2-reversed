// FUNC_NAME: Entity::checkAndDestroyIfNotReferenced
void __thiscall Entity::checkAndDestroyIfNotReferenced(int this, int param_2)

{
  int iVar1;
  int iVar2;
  int local_8 [2];
  
  iVar1 = *(int *)(param_2 + 0x24);
  for (iVar2 = *(int *)(*(int *)(param_2 + 0x24) + 0xc); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0xc))
  {
    iVar1 = iVar2;
  }
  iVar2 = 0;
  if ((*(char *)(iVar1 + 0x10) + iVar1 != 0) && (FUN_004af8c0(local_8,0x2001), local_8[0] != 0)) {
    iVar2 = local_8[0];
  }
  if ((((*(int *)(this + 0x30) == 0) || (iVar2 != *(int *)(this + 0x30))) &&
      ((*(int *)(this + 0x34) == 0 || (iVar2 != *(int *)(this + 0x34))))) &&
     ((*(int *)(this + 0x38) == 0 || (iVar2 != *(int *)(this + 0x38))))) {
    FUN_00a64940(param_2);
  }
  return;
}