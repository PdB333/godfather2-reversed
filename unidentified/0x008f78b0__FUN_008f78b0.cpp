// FUNC_NAME: SomeClass::isValueInRange
undefined1 __thiscall isValueInRange(int this, float value)
{
  undefined1 result;
  
  result = 0;
  if ((*(float *)(this + 0x8c) <= value) && (value <= *(float *)(this + 0x90))) {
    result = 1;
  }
  return result;
}