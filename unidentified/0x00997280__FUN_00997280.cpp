// FUNC_NAME: SomeClass::clearOrReset
void __fastcall SomeClass::clearOrReset(int thisPtr)
{
  int iVar1;
  int iVar2;
  int local_4;
  
  if (*(int *)(thisPtr + 0x60) != 0) {
    local_4 = 0;
    // Call virtual function at vtable+0x10 with some identifier
    (**(code **)(**(int **)(thisPtr + 0xc) + 0x10))(0xae986323, &local_4);
    
    // Release/release resource at +0x70
    FUN_009c8eb0(*(int *)(thisPtr + 0x70));
    *(int *)(thisPtr + 0x70) = 0;
    *(int *)(thisPtr + 0x6c) = 0;
    
    // Release/release resource at +0x68
    FUN_009c8f10(*(int *)(thisPtr + 0x68));
    iVar2 = 0;
    *(int *)(thisPtr + 0x68) = 0;
    
    // Iterate over array at +0x64 (offset 100 = 0x64)
    if (0 < *(int *)(thisPtr + 0x60)) {
      do {
        // Release each element in the array
        FUN_0045edc0(*(int *)(*(int *)(thisPtr + 100) + iVar2 * 4));
        FUN_009c8eb0(*(int *)(*(int *)(thisPtr + 100) + iVar2 * 4));
        iVar2 = iVar2 + 1;
      } while (iVar2 < *(int *)(thisPtr + 0x60));
    }
    
    // Release the array itself
    FUN_009c8f10(*(int *)(thisPtr + 100));
    iVar2 = 0;
    *(int *)(thisPtr + 100) = 0;
    
    // Clear some array at +0x34 (offset 52) with stride 0xC0
    if (0 < *(int *)(thisPtr + 0x38)) {
      iVar1 = 0;
      do {
        *(int *)(*(int *)(thisPtr + 0x34) + 0xa4 + iVar1) = 0;
        iVar2 = iVar2 + 1;
        iVar1 = iVar1 + 0xc0;
      } while (iVar2 < *(int *)(thisPtr + 0x38));
    }
    
    // Reset count at +0x60
    *(int *)(thisPtr + 0x60) = 0;
  }
  return;
}