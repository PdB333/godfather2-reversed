// FUNC_NAME: SomeClass::computeRandomScaledValue
float __fastcall computeRandomScaledValue(int this)
{
  float baseVal;
  int randVal;
  float scaleFactor;
  
  if (*(int *)(this + 8) != 0) {
    baseVal = *(float *)(*(int *)(this + 8) + 0x64);          // +0x64: some base value from referenced object
    scaleFactor = *(float *)(*(int *)(this + 8) + 0x68) * baseVal; // +0x68: multiplier
    randVal = _rand();
    return ((float)randVal * DAT_00e44590 * scaleFactor * DAT_00d5eee4 + baseVal) - scaleFactor;
  }
  return (float)DAT_00d5780c;  // default value when no object reference
}