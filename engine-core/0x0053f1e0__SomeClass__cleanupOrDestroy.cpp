// FUNC_NAME: SomeClass::cleanupOrDestroy
void SomeClass::cleanupOrDestroy(int param_1)
{
  int iVar1;
  int iVar2;
  int unaff_EDI;
  
  *(undefined1 *)(unaff_EDI + 0x4c) = 1; // +0x4c: some flag (e.g., m_bCleaningUp)
  if (*(char *)(unaff_EDI + 0x28) == '\0') { // +0x28: some boolean (e.g., m_bIsActive)
    FUN_009e6550(param_1); // likely a deactivation or cleanup function
  }
  else {
    FUN_005619d0(param_1); // alternative cleanup path
  }
  iVar1 = *(int *)(unaff_EDI + 0x40); // +0x40: pointer to a linked list or array (e.g., m_pChildList)
  *(undefined1 *)(unaff_EDI + 0x4c) = 0; // reset flag
  *(undefined4 *)(unaff_EDI + 0x40) = 0; // clear pointer
  while (iVar1 != 0) {
    iVar2 = *(int *)(iVar1 + 0xb0); // +0xb0: next pointer in linked list (e.g., m_pNext)
    FUN_009c8eb0(iVar1); // likely a destructor or release function
    iVar1 = iVar2;
  }
  FUN_00540670(); // final cleanup (e.g., delete this or notify manager)
  return;
}