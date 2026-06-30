// FUNC_NAME: SomeClass::removeElementAtIndex
void __fastcall SomeClass::removeElementAtIndex(undefined4 param_1, uint param_2)
{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  // param_2 is the index to remove
  // DAT_01218d30 is the count of elements in the array
  // DAT_01218a30 is the base of the array (each element is 0xC0 bytes)
  if (param_2 < DAT_01218d30) {
    // Shift elements left to fill the gap
    if (param_2 < DAT_01218d30 - 1) {
      puVar1 = (undefined4 *)(&DAT_01218a30 + param_2 * 0xc0);
      do {
        puVar3 = puVar1 + 0x30;
        puVar4 = puVar1;
        // Copy 0x30 dwords = 0xC0 bytes (one element)
        for (iVar2 = 0x30; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar4 = puVar4 + 1;
        }
        param_2 = param_2 + 1;
        puVar1 = puVar1 + 0x30;
      } while (param_2 < DAT_01218d30 - 1);
    }
    // Decrement the element count
    DAT_01218d30 = DAT_01218d30 - 1;
  }
  return;
}