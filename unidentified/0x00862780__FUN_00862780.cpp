// FUNC_NAME: SomeClass::releaseOrFreeResources
void __fastcall SomeClass::releaseOrFreeResources(int *this)
{
  // +0x0C (param_1[3]) - likely a pointer to a sub-resource or secondary buffer
  if (this[3] != 0) {
    FUN_004daf90(this + 3);  // free/release resource at offset +0x0C
  }
  // +0x00 (param_1[0]) - primary resource pointer
  if (*this != 0) {
    FUN_004daf90(this);      // free/release primary resource at offset +0x00
  }
  return;
}