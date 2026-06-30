// FUNC_NAME: SomeClass::findOrSomething
undefined4 FUN_004c9880(int param_1)
{
  int iVar1;
  int in_EAX; // this ptr (via EAX)
  int local_10;
  int local_c;
  
  if ((param_1 != 0) && (*(int *)(in_EAX + 0x10) != 0)) {
    FUN_004c9f20(&param_1); // possibly a validation/convert call
    iVar1 = *(int *)(*(int *)(in_EAX + 0x10) + 0x1c); // deref this->field+0x10, field+0x1c
    if ((local_10 == 0) || (local_10 != *(int *)(in_EAX + 0x10))) {
      FUN_00b97aea(); // error/fatal handler
    }
    if (local_c != iVar1) {
      if (local_10 == 0) {
        FUN_00b97aea();
      }
      if (local_c == *(int *)(local_10 + 0x1c)) {
        FUN_00b97aea();
      }
      return *(undefined4 *)(local_c + 0x10); // return value from local_c+0x10
    }
  }
  return 0;
}