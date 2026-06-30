// FUNC_NAME: SomeClass::updateSomeList
void SomeClass::updateSomeList(undefined4 param_1)
{
  int iVar1;
  int iVar2;
  int this = unaff_EDI; // this pointer, likely from EDI register
  
  // Check if the primary object at offset +0x64 (100) is non-null
  if (*(int *)(this + 0x64) != 0) {
    FUN_005822d0(param_1); // Likely a function to process/update the object
  }
  
  iVar2 = 0;
  // Loop through an array of objects, count stored at +0x2e4
  if (0 < *(int *)(this + 0x2e4)) {
    iVar1 = 0;
    do {
      // Each element is 0xe0 bytes, check the object at offset +0x64 within each element
      if (*(int *)(*(int *)(this + 0x2ec) + iVar1 + 0x64) != 0) {
        FUN_005822d0(param_1);
      }
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 0xe0;
    } while (iVar2 < *(int *)(this + 0x2e4));
  }
  return;
}