// FUNC_NAME: SomeManager::pairOperation
uint __thiscall pairOperation(int param_1, int param_2, int param_3, undefined4 param_4, undefined4 param_5)

{
  int *piVar1;
  int *piVar2;
  int firstEntry;
  int secondEntry;
  uint result;
  
  // Array of 0xC-byte entries at offset 0x70: each entry = { int handle, int field4, int field8 }
  piVar1 = (int *)(param_3 + 0x70 + param_1 * 0xc);
  firstEntry = *piVar1;

  // Mask out lower byte (preserve high 24 bits of previous EAX? or error code)
  result = in_EAX & 0xffffff00;

  if (firstEntry != 0) {
    piVar2 = (int *)(param_3 + 0x70 + param_2 * 0xc);
    secondEntry = *piVar2;
    if (secondEntry != 0) {
      // Both entries valid – compute using their handle and field at +8
      result = FUN_00862820(firstEntry, piVar1[2], secondEntry, piVar2[2], param_4, param_5);
    }
  }

  return result;
}