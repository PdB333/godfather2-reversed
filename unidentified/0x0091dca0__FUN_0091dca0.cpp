// FUNC_NAME: SomeClass::handleStateChange
void __fastcall SomeClass::handleStateChange(int thisPtr)
{
  if (*(int *)(thisPtr + 0xb8) == 1) {
    FUN_00402050(&DAT_01130448, 0);
  }
  else if (*(int *)(thisPtr + 0xb8) - 10U < 0x10) {
    FUN_00402050(&DAT_01130448, 0);
    FUN_009171b0();
    *(undefined4 *)(thisPtr + 0xc0) = 0;
    *(undefined4 *)(thisPtr + 0xb4) = 0;
    FUN_0091cd80(1, DAT_00e54d0c);
    return;
  }
  return;
}