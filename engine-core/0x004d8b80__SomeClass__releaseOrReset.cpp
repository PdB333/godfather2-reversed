// FUNC_NAME: SomeClass::releaseOrReset
void SomeClass::releaseOrReset(void)
{
  int iVar1;
  
  iVar1 = *(int *)(this + 0x20); // +0x20: pointer to child/owned object
  *this = 1; // +0x00: flag indicating released/reset state
  if (iVar1 != 0) {
    if (*(int *)(iVar1 + 0x20) != 0) { // child also has an owned object
      FUN_004d8bc0(1); // release child's child
    }
    FUN_009c8eb0(iVar1); // free/deallocate child object
  }
  *(int *)(this + 0x20) = 0; // clear owned pointer
  return;
}