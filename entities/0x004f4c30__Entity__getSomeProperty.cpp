// FUNC_NAME: Entity::getSomeProperty
undefined4 Entity::getSomeProperty(int param_1, int param_2)
{
  undefined4 uVar1;
  
  if (param_2 != 0) {
    // Access entity data at offset +0x4, then +0xC for property value
    uVar1 = FUN_004f5090(*(undefined4 *)(*(int *)(param_1 + 4) + 0xc));
    return uVar1;
  }
  return 0;
}