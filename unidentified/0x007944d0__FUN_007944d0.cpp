// FUNC_NAME: SomeClass::setSomeFlag
void __thiscall SomeClass::setSomeFlag(int this, char enable)
{
  if (enable != '\0') {
    *(uint *)(this + 700) = *(uint *)(this + 700) | 0x40000;
    return;
  }
  *(uint *)(this + 700) = *(uint *)(this + 700) & 0xfffbffff;
  return;
}