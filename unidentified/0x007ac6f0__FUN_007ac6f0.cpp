// FUNC_NAME: SomeClass::setSomeFloatValue
void __thiscall setSomeFloatValue(int this, float value)
{
  if (value != *(float *)(this + 0x48)) {
    *(undefined1 *)(this + 100) = 1;  // +0x64: dirty flag or changed indicator
    *(float *)(this + 0x48) = value;  // +0x48: stored float value
  }
  return;
}