// FUNC_NAME: SomeClass::getSomePointer
int __fastcall SomeClass::getSomePointer(int this)
{
  if (*(int *)(this + 8) != 0) {
    return *(int *)(this + 8) + -0x48;
  }
  return 0;
}