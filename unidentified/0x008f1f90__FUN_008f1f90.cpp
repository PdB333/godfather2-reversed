// FUNC_NAME: SomeClass::setName
void __thiscall SomeClass::setName(int this, char *name)
{
  _strncpy((char *)(this + 0x2050), name, 0x3f); // +0x2050: name buffer (63 chars max)
  *(undefined1 *)(this + 0x208f) = 0; // +0x208f: null terminator
  return;
}