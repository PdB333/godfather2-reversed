// FUNC_NAME: SomeClass::releaseResources
void __fastcall SomeClass::releaseResources(int this)
{
  int iVar1;
  
  iVar1 = *(int *)(this + 0x78);
  if (iVar1 != 0) {
    FUN_00816660(); // likely some pre-release or cleanup function
    FUN_009c8eb0(iVar1); // likely a memory deallocation or resource release function
    *(int *)(this + 0x78) = 0; // +0x78: pointer to first resource
  }
  iVar1 = *(int *)(this + 0x7c);
  if (iVar1 != 0) {
    FUN_00816660(); // same pre-release function
    FUN_009c8eb0(iVar1); // same deallocation function
    *(int *)(this + 0x7c) = 0; // +0x7c: pointer to second resource
  }
  return;
}