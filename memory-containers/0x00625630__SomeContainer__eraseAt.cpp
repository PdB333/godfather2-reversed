// FUNC_NAME: SomeContainer::eraseAt
void __fastcall SomeContainer::eraseAt(undefined4 param_1, int param_2, int thisPtr)
{
  int iVar1;
  undefined4 *puVar2;
  int unaff_ESI;
  
  // param_1 is likely unused or the this pointer passed via ECX, check ESI being used as this
  // unaff_ESI is presumably the 'this' pointer, stored in ESI by the caller
  if (param_2 < 1) {
    iVar1 = FUN_00625430();
  }
  else {
    // +0x0C: likely size or capacity field
    iVar1 = *(int *)(unaff_ESI + 0xc) + -8 + param_2 * 8;
  }
  puVar2 = (undefined4 *)(iVar1 + 8);
  if (puVar2 < *(undefined4 **)(unaff_ESI + 8)) {
    // +0x08: pointer to end of allocated memory (or end of used data)
    do {
      puVar2[-2] = *puVar2;
      puVar2[-1] = puVar2[1];
      puVar2 = puVar2 + 2;
    } while (puVar2 < *(undefined4 **)(unaff_ESI + 8));
  }
  // +0x08: decrement count or pointer (removing one 8-byte element)
  *(int *)(unaff_ESI + 8) = *(int *)(unaff_ESI + 8) + -8;
  return;
}