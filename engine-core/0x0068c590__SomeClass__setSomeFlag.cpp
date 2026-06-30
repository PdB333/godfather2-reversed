// FUNC_NAME: SomeClass::setSomeFlag
void __thiscall setSomeFlag(int this, char flagValue)
{
  *(char *)(this + 0x15) = flagValue; // +0x15: some flag byte
  *(int *)(this + 0x18) = 0;          // +0x18: some counter/state, reset to 0
  return;
}