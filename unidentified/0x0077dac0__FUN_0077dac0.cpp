// FUNC_NAME: SomeContainer::addEntry
void __thiscall SomeContainer::addEntry(int this, int param_2)
{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  
  iVar3 = DAT_01205228;
  if (param_2 != 0) {
    iVar1 = *(int *)(param_2 + 0x50); // +0x50: some ID field
    uVar2 = *(uint *)(this + 0x11c); // +0x11c: count of entries
    param_2 = DAT_00d5ccf8;
    uVar4 = 0;
    if (uVar2 != 0) {
      piVar5 = (int *)(this + 0x5c); // +0x5c: start of entry array (each entry 12 bytes: ID, value1, value2)
      do {
        if (*piVar5 == iVar1) {
          param_2 = piVar5[2]; // existing entry's second value
          if (uVar4 != 0xffffffff) goto LAB_0077db2f;
          break;
        }
        uVar4 = uVar4 + 1;
        piVar5 = piVar5 + 3; // advance by 3 ints (12 bytes)
      } while (uVar4 < uVar2);
    }
    if (0xf < uVar2) {
      uVar4 = 0;
LAB_0077db2f:
      FUN_0077d900(uVar4); // some cleanup/removal function
    }
    piVar5 = (int *)(this + 0x5c + *(int *)(this + 0x11c) * 0xc); // point to next free slot
    *(int *)(this + 0x11c) = *(int *)(this + 0x11c) + 1; // increment count
    piVar5[1] = iVar3; // set second value (timestamp or sequence?)
    *piVar5 = iVar1; // set ID
    piVar5[2] = param_2; // set third value (some context)
  }
  return;
}