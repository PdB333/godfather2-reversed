// FUNC_NAME: SomeClass::getOrCreateSubObject
int __fastcall SomeClass::getOrCreateSubObject(int this)
{
  if (*(int *)(this + 0x54) == 0) {
    FUN_00603330(*(undefined4 *)(this + 0x70), this + 0x50);
  }
  return this + 0x50;
}