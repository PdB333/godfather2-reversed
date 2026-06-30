// FUNC_NAME: SomeClass::incrementAndReturnCounter
int __fastcall incrementAndReturnCounter(int this)
{
  *(int *)(this + 0x18) = *(int *)(this + 0x18) + 1;  // +0x18: counter field
  return *(int *)(this + 0x18);  // return the incremented value
}