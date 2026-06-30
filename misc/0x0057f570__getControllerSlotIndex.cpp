// FUNC_NAME: getControllerSlotIndex
uint getControllerSlotIndex(void)
{
  uint uVar1;
  
  uVar1 = __aullshr();
  return uVar1 & 3;
}