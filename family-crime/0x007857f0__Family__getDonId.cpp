// FUNC_NAME: Family::getDonId
__fastcall FUN_007857f0(int param_1)
{
  // Returns the don character data ID from the family data structure at offset +0x2c88,
  // which points to a structure where the don's ID is stored at offset +0x94.
  return *(int *)(*(int *)(param_1 + 0x2c88) + 0x94);
}