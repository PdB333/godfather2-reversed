// FUNC_NAME: Entity::getSomeFlagOrState
uint Entity::getSomeFlagOrState(undefined4 param_1)
{
  int *piVar1;
  uint uVar2;
  
  piVar1 = (int *)FUN_004baf90(param_1); // likely Entity::getInternalData or similar
  if ((piVar1 != (int *)0x0) && (*piVar1 == 0)) {
    uVar2 = FUN_008b5980(param_1); // likely Entity::getStateFlags or similar
    return uVar2 & 0xffff;
  }
  return (uint)piVar1 & 0xffff0000;
}