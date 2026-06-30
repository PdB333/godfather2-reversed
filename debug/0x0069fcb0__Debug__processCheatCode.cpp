// FUNC_NAME: Debug::processCheatCode
void Debug::processCheatCode(uint param_1, uint param_2, uint param_3, int param_4, uint param_5)
{
  int iVar1;
  char *puVar2;
  
  iVar1 = FUN_00483a50(); // getCurrentGameState
  if (iVar1 == 1) { // game state == playing
    FUN_004e4e10(2, param_1); // executeCheat(2, param_1)
  }
  iVar1 = FUN_00483a50(); // getCurrentGameState
  if (iVar1 == 1) {
    DAT_0120546f = (char)(param_1 >> 8) == '\0'; // some global flag
  }
  iVar1 = FUN_00483a50(); // getCurrentGameState
  if (iVar1 == 1) {
    FUN_004e4e10(4, CONCAT13(param_2._1_1_, CONCAT12((undefined1)param_2, (short)(param_1 >> 0x10))));
  }
  iVar1 = FUN_00483a50(); // getCurrentGameState
  if (iVar1 == 1) {
    FUN_004e4e10(0x10, CONCAT13(param_2._2_1_, CONCAT12(param_2._1_1_, CONCAT11((undefined1)param_2, param_1._3_1_))));
  }
  iVar1 = FUN_00483a50(); // getCurrentGameState
  if (iVar1 == 1) {
    FUN_004e4e10(1, param_2);
    FUN_004e4e10(0xf, param_2);
    FUN_004e4e10(0xe, param_2);
  }
  iVar1 = FUN_00483a50(); // getCurrentGameState
  if (iVar1 == 1) {
    FUN_004e4e10(0xb, CONCAT13((undefined1)param_3, (int3)(param_2 >> 8)));
  }
  iVar1 = FUN_00483a50(); // getCurrentGameState
  if (iVar1 == 1) {
    iVar1 = FUN_004e4040(0x2e616d62); // findObjectByHash(".amb")
    if (iVar1 != 0) {
      if (param_2._2_1_ == '\0') {
        *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) | 1; // set flag bit 0
      }
      else {
        *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xfffffffe; // clear flag bit 0
      }
    }
  }
  iVar1 = FUN_00483a50(); // getCurrentGameState
  if (iVar1 == 1) {
    iVar1 = FUN_004e4040(0x2e666c72); // findObjectByHash(".flr")
    if (iVar1 != 0) {
      if (param_2._3_1_ == '\0') {
        *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) | 1;
      }
      else {
        *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xfffffffe;
      }
    }
    iVar1 = FUN_004e4040(0x2e666c63); // findObjectByHash(".flc")
    if (iVar1 != 0) {
      if (param_2._3_1_ == '\0') {
        *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) | 1;
      }
      else {
        *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xfffffffe;
      }
    }
  }
  iVar1 = FUN_00483a50(); // getCurrentGameState
  if (iVar1 == 1) {
    puVar2 = (char *)FUN_0041d1f0(); // getSomeGlobalPointer
    *puVar2 = (char)param_3;
  }
  iVar1 = FUN_00483a50(); // getCurrentGameState
  if (iVar1 == 1) {
    DAT_012054eb = param_3._1_1_ == '\0';
    DAT_012054fc = DAT_012054eb;
  }
  iVar1 = FUN_00483a50(); // getCurrentGameState
  if (iVar1 == 1) {
    FUN_0060e610(param_4); // some function with int param
    if (param_4 == 0) {
      FUN_00413c90(); // resetSomething
    }
  }
  iVar1 = FUN_00483a50(); // getCurrentGameState
  if (iVar1 == 1) {
    FUN_0069fc50(param_5); // another cheat processing function
  }
  return;
}