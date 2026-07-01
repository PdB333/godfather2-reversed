// FUNC_NAME: SomeClass::setName
void __thiscall SomeClass::setName(int this, char *name)
{
  // +0x40: name buffer (0x100 bytes, last byte used as null terminator? offset 0x13f)
  _strncpy((char *)(this + 0x40), name, 0xff);
  *(undefined1 *)(this + 0x13f) = 0; // +0x13f: null terminator for the name buffer
  return;
}