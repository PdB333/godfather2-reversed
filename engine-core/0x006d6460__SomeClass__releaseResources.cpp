// FUNC_NAME: SomeClass::releaseResources
void __fastcall SomeClass::releaseResources(int this)
{
  if (*(int *)(this + 0x30) != 0) {
    FUN_004daf90(this + 0x30); // Release resource at +0x30
  }
  if (*(int *)(this + 0x28) != 0) {
    FUN_004daf90(this + 0x28); // Release resource at +0x28
  }
  return;
}