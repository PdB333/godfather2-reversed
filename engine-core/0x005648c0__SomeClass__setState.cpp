// FUNC_NAME: SomeClass::setState
void __fastcall SomeClass::setState(int this)
{
  if (*(int *)(this + 0xc) != 5) {
    *(int *)(this + 4) = *(int *)(this + 0xc);
    return;
  }
  *(int *)(this + 4) = 5;
  return;
}