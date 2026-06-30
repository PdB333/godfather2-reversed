// FUNC_NAME: SomeClass::updateStateMachine
void SomeClass::updateStateMachine(void)
{
  byte bVar1;
  int iVar2;
  uint uVar3;
  
  bVar1 = **(byte **)(this + 0x4c);
  if ((bVar1 & 1) == 0) {
    if ((bVar1 & 2) == 0) {
      if ((bVar1 & 0x40) == 0) goto LAB_00580111;
      // +0x58: some counter
      *(int *)(this + 0x58) = *(int *)(this + 0x58) + 9;
    }
    else {
      uVar3 = __aullshr();
      if (2 < (uVar3 & 3) - 1) {
        // +0x4c: state flags pointer? calling some function twice
        FUN_0057f330();
        FUN_0057f330();
      }
      FUN_0057f330();
    }
    // +0x08, +0x10: counters
    *(int *)(this + 8) = *(int *)(this + 8) + 6;
    *(int *)(this + 0x10) = *(int *)(this + 0x10) + 1;
  }
  else {
    // +0x14, +0x18: counters
    *(int *)(this + 0x14) = *(int *)(this + 0x14) + 6;
    *(int *)(this + 0x18) = *(int *)(this + 0x18) + 1;
  }
LAB_00580111:
  bVar1 = **(byte **)(this + 0x4c);
  if ((bVar1 & 0x1c) == 0) {
    if ((bVar1 & 0x20) == 0) {
      // +0x44, +0x48, +0x50, +0x4c: counters
      *(int *)(this + 0x44) = *(int *)(this + 0x44) + 0xc;
      *(int *)(this + 0x48) = *(int *)(this + 0x48) + 1;
      *(int *)(this + 0x50) = *(int *)(this + 0x50) + 1;
      *(int *)(this + 0x4c) = *(int *)(this + 0x4c) + 1;
      return;
    }
  }
  else {
    if ((bVar1 & 0x10) != 0) {
      iVar2 = *(int *)(this + 0x28);
      uVar3 = __aullshr();
      if ((uVar3 & 3) - 1 < 3) {
        // +0x1c, +0x20, +0x50, +0x28, +0x4c: counters
        *(int *)(this + 0x1c) = *(int *)(this + 0x1c) + 1;
        *(int *)(this + 0x20) = *(int *)(this + 0x20) + 0xc;
        *(int *)(this + 0x50) = *(int *)(this + 0x50) + 1;
        *(int *)(this + 0x28) = iVar2 + 1;
        *(int *)(this + 0x4c) = *(int *)(this + 0x4c) + 1;
        return;
      }
      // +0x1c, +0x20, +0x50, +0x28, +0x4c: counters
      *(int *)(this + 0x1c) = *(int *)(this + 0x1c) + 3;
      *(int *)(this + 0x20) = *(int *)(this + 0x20) + 0xc;
      *(int *)(this + 0x50) = *(int *)(this + 0x50) + 1;
      *(int *)(this + 0x28) = iVar2 + 1;
      *(int *)(this + 0x4c) = *(int *)(this + 0x4c) + 1;
      return;
    }
    if ((bVar1 & 8) != 0) {
      iVar2 = *(int *)(this + 0x38);
      uVar3 = __aullshr();
      if ((uVar3 & 3) - 1 < 3) {
        // +0x2c, +0x30, +0x50, +0x38, +0x4c: counters
        *(int *)(this + 0x2c) = *(int *)(this + 0x2c) + 2;
        *(int *)(this + 0x30) = *(int *)(this + 0x30) + 0xc;
        *(int *)(this + 0x50) = *(int *)(this + 0x50) + 1;
        *(int *)(this + 0x38) = iVar2 + 1;
        *(int *)(this + 0x4c) = *(int *)(this + 0x4c) + 1;
        return;
      }
      // +0x2c, +0x30, +0x50, +0x38, +0x4c: counters
      *(int *)(this + 0x2c) = *(int *)(this + 0x2c) + 6;
      *(int *)(this + 0x30) = *(int *)(this + 0x30) + 0xc;
      *(int *)(this + 0x50) = *(int *)(this + 0x50) + 1;
      *(int *)(this + 0x38) = iVar2 + 1;
      *(int *)(this + 0x4c) = *(int *)(this + 0x4c) + 1;
      return;
    }
    // +0x3c, +0x40: counters
    *(int *)(this + 0x3c) = *(int *)(this + 0x3c) + 0xc;
    *(int *)(this + 0x40) = *(int *)(this + 0x40) + 1;
  }
  // +0x50, +0x4c: counters
  *(int *)(this + 0x50) = *(int *)(this + 0x50) + 1;
  *(int *)(this + 0x4c) = *(int *)(this + 0x4c) + 1;
  return;
}