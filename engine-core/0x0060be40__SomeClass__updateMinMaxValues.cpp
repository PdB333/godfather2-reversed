// FUNC_NAME: SomeClass::updateMinMaxValues
void SomeClass::updateMinMaxValues(void)
{
  ushort currentValue;
  uint index;
  ushort maxValue;
  int thisPtr; // unaff_ESI
  ushort minValue;

  index = 0;
  minValue = 0;
  maxValue = 0xffff;
  if (*(int *)(thisPtr + 0xc) != 0) { // +0xC: count of values
    do {
      currentValue = *(ushort *)(*(int *)(thisPtr + 0x14) + index * 2); // +0x14: pointer to values array
      if (currentValue < maxValue) {
        maxValue = currentValue;
      }
      if (minValue <= currentValue) {
        minValue = currentValue;
      }
      index = index + 1;
    } while (index < *(uint *)(thisPtr + 0xc));
  }
  *(ushort *)(thisPtr + 0x12) = minValue; // +0x12: stored min value
  *(ushort *)(thisPtr + 0x10) = maxValue; // +0x10: stored max value
  return;
}