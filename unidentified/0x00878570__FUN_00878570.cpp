// FUNC_NAME: SomeClass::releaseManagedResources
void __fastcall SomeClass::releaseManagedResources(int thisPtr)
{
  // Release resources at various offsets if they are non-null
  if (*(int *)(thisPtr + 0xa04) != 0) {
    FUN_004df6e0(); // likely a release/free function
  }
  if (*(int *)(thisPtr + 0xa08) != 0) {
    FUN_004df6e0();
  }
  if (*(int *)(thisPtr + 0xa0c) != 0) {
    FUN_004df6e0();
  }
  if (*(int *)(thisPtr + 0xb6c) != 0) {
    FUN_004df6e0();
  }
  if (*(int *)(thisPtr + 0xb70) != 0) {
    FUN_004df6e0();
  }
  if (*(int *)(thisPtr + 0xb74) != 0) {
    FUN_004df6e0();
  }
  if (*(int *)(thisPtr + 0xb78) != 0) {
    FUN_004df6e0();
    return;
  }
  return;
}