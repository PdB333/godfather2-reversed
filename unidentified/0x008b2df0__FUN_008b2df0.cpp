// FUNC_NAME: SomeClass::isValidForTarget
uint __thiscall SomeClass::isValidForTarget(int thisPtr, int param2)
{
  uint result;

  if (*(int *)(thisPtr + 0x74) == 0) {
    result = FUN_00446100(thisPtr + 100, 0);
    *(uint *)(thisPtr + 0x74) = result;
  }
  if (*(int *)(thisPtr + 0x74) != 0) {
    if ((param2 != DAT_00e54378) && (param2 != *(int *)(*(int *)(thisPtr + 0x74) + 0x50))) {
      return 0;
    }
    return 1;
  }
  return result & 0xffffff00;
}