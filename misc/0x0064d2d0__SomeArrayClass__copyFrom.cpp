// FUNC_NAME: SomeArrayClass::copyFrom
void SomeArrayClass::copyFrom(int param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  uint count; // unaff_ESI - number of elements to copy
  int buffer; // unaff_EDI - pointer to destination array
  
  uVar2 = 0;
  if (count != 0) {
    do {
      // Calculate pointer to destination element at index uVar2
      // +0x8 is likely the array data pointer offset in the class
      puVar1 = (undefined4 *)(*(int *)(buffer + 8) + uVar2 * 4);
      if (puVar1 != (undefined4 *)0x0) {
        // Copy a 4-byte value from source (param_1) to destination
        *puVar1 = *(undefined4 *)(uVar2 * 4 + param_1);
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < count);
  }
  return;
}