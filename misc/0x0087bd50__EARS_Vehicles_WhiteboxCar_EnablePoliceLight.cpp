// Xbox PDB: EARS_Vehicles_WhiteboxCar_EnablePoliceLight
// FUNC_NAME: PlayerF2FSM::handleCherryBombInput
void __thiscall PlayerF2FSM::handleCherryBombInput(int thisPtr, int param_2)
{
  undefined4 uVar1;
  
  if ((char)param_2 == '\0') {
    if (*(int *)(thisPtr + 0xa0c) != 0) {
      // Release cherry bomb if currently holding one
      FUN_004df590();
      return;
    }
  }
  else if ((((*(int *)(thisPtr + 0x9e0) != 0) || (*(int *)(thisPtr + 0x9e4) != 0)) ||
           (*(int *)(thisPtr + 0x9e8) != 0)) || (*(int *)(thisPtr + 0x9ec) != 0)) {
    // Check if any of the four cherry bomb slots are occupied
    if (*(int *)(thisPtr + 0xa0c) != 0) {
      // Already holding a cherry bomb, throw it
      FUN_004df5c0();
      return;
    }
    // Find available cherry bomb slot and attach "BP_cherry_L" bone
    uVar1 = FUN_0087bac0(&param_2, thisPtr + 0x9e0, "BP_cherry_L");
    FUN_00414db0(uVar1);
    if (param_2 != 0) {
      *(undefined4 *)(param_2 + 8) = 0;
    }
  }
  return;
}