// FUNC_NAME: unknown::getSomethingWithOffset
int unknown::getSomethingWithOffset(int param_1)
{
  // Accesses two fields at offsets +0x3c and +0x38 from the object
  // Multiplies their sum by 0x14 and adds 0x60
  return (*(int *)(param_1 + 0x3c) + *(int *)(param_1 + 0x38)) * 0x14 + 0x60;
}