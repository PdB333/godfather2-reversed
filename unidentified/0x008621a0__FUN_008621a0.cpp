// FUNC_NAME: SomeClass::releaseOrFreeResources
void __fastcall SomeClass::releaseOrFreeResources(int *this)
{
  if (this[3] != 0) {
    FUN_004daf90(this + 3); // Free/release resource at offset +0x0C
  }
  if (*this != 0) {
    FUN_004daf90(this); // Free/release resource at offset +0x00
  }
  return;
}