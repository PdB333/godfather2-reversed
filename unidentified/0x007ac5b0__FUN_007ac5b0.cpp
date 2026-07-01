// FUNC_NAME: SomeClass::setSomeFloatValue
void __thiscall setSomeFloatValue(int this, float newValue)
{
  if (newValue != *(float *)(this + 0x1c)) {
    *(uint8_t *)(this + 100) = 1; // +0x64: dirty flag or changed indicator
    *(float *)(this + 0x1c) = newValue; // +0x1c: stored float value
  }
  return;
}