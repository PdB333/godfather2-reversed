// FUNC_NAME: PlayerSM::updateState
void __thiscall PlayerSM::updateState(void)
{
  char state;
  int thisPtr; // unaff_ESI
  
  // Check if bit 10 (0x400) is set in flags at +0x2c
  if ((*(uint *)(thisPtr + 0x2c) >> 10 & 1) != 0) {
    // Clear bit 10
    FUN_00566af0();
    *(uint *)(thisPtr + 0x2c) = *(uint *)(thisPtr + 0x2c) & 0xfffffbff;
  }
  // Check if bit 9 (0x200) is set in flags at +0x2c
  if ((*(uint *)(thisPtr + 0x2c) >> 9 & 1) != 0) {
    FUN_00af3560();
    FUN_00566af0();
    *(uint *)(thisPtr + 0x2c) = *(uint *)(thisPtr + 0x2c) & 0xfffffdff;
    FUN_00b02ab0();
    return;
  }
  state = *(char *)(thisPtr + 0x14);
  if (state == '\x03') {
    FUN_00af3560();
    *(undefined1 *)(thisPtr + 0x14) = 4;
    FUN_00b02ab0();
    return;
  }
  if ((state == '\x01') || (state == '\x02')) {
    FUN_00566b70();
  }
  else if (*(int *)(thisPtr + 0x10) == 9) {
    if ((*(uint *)(thisPtr + 0x2c) >> 0xb & 1) == 0) {
      *(undefined1 *)(thisPtr + 0x14) = 2;
      *(undefined4 *)(thisPtr + 0x10) = 0;
      FUN_00b02ab0();
      return;
    }
    *(undefined4 *)(thisPtr + 0x10) = 10;
    if (*(code **)(thisPtr + 0x120) != (code *)0x0) {
      (**(code **)(thisPtr + 0x120))(*(undefined4 *)(thisPtr + 0x18));
      FUN_00b02ab0();
      return;
    }
  }
  FUN_00b02ab0();
  return;
}