// FUNC_NAME: SomeClass::setSomeId
void __thiscall setSomeId(int *this, int newId)
{
  if (newId != *this) {
    this[6] = DAT_01205228; // +0x18: some timestamp or version field
    *this = newId; // +0x00: the id field
  }
  return;
}