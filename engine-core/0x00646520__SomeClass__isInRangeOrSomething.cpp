// FUNC_NAME: SomeClass::isInRangeOrSomething
uint __fastcall SomeClass::isInRangeOrSomething(int this, uint param_2)
{
  uint *in_EAX;
  
  if (*(uint *)(this + 0x468) != 0) {
    for (in_EAX = *(uint **)(this + 0x464); in_EAX != (uint *)(this + 0x448);
        in_EAX = (uint *)in_EAX[7]) {
      if ((*in_EAX <= param_2) && (param_2 < in_EAX[1] + *in_EAX)) {
        return (uint)(*(uint *)(this + 0x468) < param_2);
      }
    }
  }
  return (uint)in_EAX & 0xffffff00;
}