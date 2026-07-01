// FUNC_NAME: DebugMenu::printDebugString
void DebugMenu::printDebugString(uint this)
{
  uint uVar1;
  undefined1 *puVar2;
  uint uVar3;
  undefined1 *local_20;
  undefined4 local_1c;
  undefined4 local_18;
  code *local_14;
  int local_10;
  undefined4 local_c;
  code *local_4;
  
  uVar1 = this;
  FUN_004dbb10(0,0,0); // likely consoleOutputBegin or similar
  FUN_004dbbb0(0x1f); // setConsoleColor? 0x1f = white on blue
  local_20 = (undefined1 *)0x0;
  local_1c = 0;
  local_18 = 0;
  local_14 = (code *)0x0;
  FUN_008f22f0(&local_20); // getDebugStringBuffer
  puVar2 = local_20;
  if (local_20 == (undefined1 *)0x0) {
    puVar2 = &DAT_0120546e; // empty string fallback
  }
  FUN_004dba80(puVar2,local_1c); // consolePrintString
  FUN_004dbd90(local_10,0,local_c); // consolePrintNewline
  if (local_10 != 0) {
    (*local_4)(local_10); // cleanup callback
  }
  uVar3 = *(uint *)(uVar1 + 4); // +0x04: some counter/index
  while (uVar3 < 0x1f) {
    uVar3 = DAT_010c2678 & DAT_012054b4; // random seed manipulation
    DAT_012054b4 = DAT_012054b4 + 1;
    this = (uint)(ushort)(short)(char)('0' - (char)(int)(*(float *)(&DAT_010c2680 + uVar3 * 4) *
                                                           _DAT_00d81184)); // convert float to digit char
    FUN_004dbd90(&this,0,1); // consolePrintChar
    uVar3 = *(uint *)(uVar1 + 4);
  }
  if (local_20 != (undefined1 *)0x0) {
    (*local_14)(local_20); // free buffer
  }
  return;
}