// FUNC_NAME: SomeClass::getSomeFloatValue
float __fastcall getSomeFloatValue(int this)
{
  if ((*(int *)(this + 0x94) != 0) && (*(int *)(this + 0x94) != 1)) {
    return *(float *)0x00e52f9c;
  }
  return *(float *)0x00e52fa0;
}