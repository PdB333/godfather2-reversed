// FUNC_NAME: SomeClass::clearStringBuffer
void __fastcall SomeClass::clearStringBuffer(int this)
{
  _strncpy((char *)(this + 0x2050), "", 0x3f); // Clear string buffer at +0x2050, max length 0x3f (63 chars)
  *(char *)(this + 0x208f) = 0; // Null-terminate at +0x208f
  return;
}