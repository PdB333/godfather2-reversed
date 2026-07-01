// FUNC_NAME: SomeClass::releaseResources
void __fastcall SomeClass::releaseResources(int thisPtr)
{
  if (*(int *)(thisPtr + 0xa04) != 0) {
    // Release resource at +0xA04
    FUN_004df600();
  }
  if (*(int *)(thisPtr + 0xa08) != 0) {
    // Release resource at +0xA08
    FUN_004df600();
    return;
  }
  return;
}