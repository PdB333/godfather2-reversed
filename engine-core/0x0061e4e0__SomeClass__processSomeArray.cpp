// FUNC_NAME: SomeClass::processSomeArray
void SomeClass::processSomeArray(void)
{
  int iVar1;
  int in_EAX; // this pointer
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(in_EAX + 0x30); // +0x30: current index
  iVar1 = *(int *)(in_EAX + 8) * 4; // +0x08: element stride (multiplied by 4 for byte offset)
  *(undefined4 *)(in_EAX + 0x38) = 0; // +0x38: some counter/flag reset
  if (iVar3 < *(int *)(in_EAX + 0x34)) { // +0x34: element count
    iVar2 = iVar3 * iVar1;
    do {
      *(int *)(in_EAX + 0x58) = *(int *)(in_EAX + 0xc) * iVar3 + *(int *)(in_EAX + 0x48); // +0x58: computed destination, +0x0c: multiplier, +0x48: base
      *(int *)(in_EAX + 0x50) = *(int *)(in_EAX + 0x40) + iVar2; // +0x50: computed source, +0x40: base source
      FUN_0061e410(iVar3); // process element at index iVar3
      iVar3 = iVar3 + 1;
      iVar2 = iVar2 + iVar1;
    } while (iVar3 < *(int *)(in_EAX + 0x34));
  }
  return;
}