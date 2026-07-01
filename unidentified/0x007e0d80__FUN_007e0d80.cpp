// FUNC_NAME: SomeClass::getSomePointer
int __fastcall SomeClass::getSomePointer(int this)
{
  if (*(int *)(this + 0x124) != 0) {
    return *(int *)(this + 0x124) + -0x48;
  }
  return 0;
}