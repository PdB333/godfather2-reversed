// FUNC_NAME: Entity::getSomePointer
uint32_t Entity::getSomePointer(uint32_t param_1)
{
  int iVar1;
  
  iVar1 = FUN_00889ee0(param_1);
  if (iVar1 != 0) {
    return *(uint32_t *)(iVar1 + 0x14); // +0x14: some pointer field
  }
  return 0;
}