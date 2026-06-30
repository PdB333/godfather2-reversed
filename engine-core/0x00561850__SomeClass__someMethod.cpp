// FUNC_NAME: SomeClass::someMethod
void SomeClass::someMethod(void)
{
  int in_EAX;
  int iVar1;
  
  FUN_00561950();
  iVar1 = *(int *)(in_EAX + 0x14c); // +0x14c: some index/offset field
  if (-1 < iVar1) {
    TlsGetValue(DAT_01139810);
    FUN_00aa26e0(*(undefined4 *)(in_EAX + 0x144),iVar1 * 4,0x17); // +0x144: some data pointer
  }
  FUN_00aad100();
  FUN_00aad100();
  iVar1 = 5;
  do {
    thunk_FUN_00aa6490();
    iVar1 = iVar1 + -1;
  } while (-1 < iVar1);
  return;
}