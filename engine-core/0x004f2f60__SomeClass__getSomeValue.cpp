// FUNC_NAME: SomeClass::getSomeValue
undefined4 FUN_004f2f60(int this, int param_2)

{
  undefined4 result;
  
  if (param_2 != 0) {
    // Dereference this+4 to get a pointer, then add 0xC to get another pointer,
    // then call FUN_004f2de0 with that value
    result = FUN_004f2de0(*(undefined4 *)(*(int *)(this + 4) + 0xc));
    return result;
  }
  return 0;
}