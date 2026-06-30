// FUNC_NAME: SomeClass::updateSomeState
void __fastcall SomeClass::updateSomeState(int param_1)
{
  // Check various state conditions
  // +0x16c: some index/state field
  // +0xfc: some integer flag
  // +0x100: some float value
  // +0x174: some integer flag
  // +0xb8: some integer flag
  // +0x74: some integer flag
  // +0x6c: some integer flag
  // +0x68: some integer field
  // +0x58: some integer field
  // +0x5c: some unsigned integer field
  // +0x60: some unsigned integer field
  if ((((((&DAT_00e50d10)[*(int *)(param_1 + 0x16c) * 0x10] == '\0') &&
        (*(int *)(param_1 + 0xfc) == 0)) && (*(float *)(param_1 + 0x100) <= _DAT_00d577a0)) &&
      ((*(int *)(param_1 + 0x174) == 0 && (*(int *)(param_1 + 0xb8) == 0)))) &&
     ((*(int *)(param_1 + 0x16c) != 0 ||
      ((*(int *)(param_1 + 0x74) == 0 &&
       (((*(int *)(param_1 + 0x6c) == 0 || (*(int *)(param_1 + 0x68) != *(int *)(param_1 + 0x58)))
        || (*(uint *)(param_1 + 0x5c) < *(uint *)(param_1 + 0x60))))))))
  {
    // Condition met: call disable function
    FUN_004086d0(&DAT_012069c4);
    return;
  }
  // Condition not met: call enable function
  FUN_00408680(&DAT_012069c4);
  return;
}