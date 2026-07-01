// FUNC_NAME: PlayerSM::handleStateTransition
void __fastcall PlayerSM::handleStateTransition(int thisPtr)
{
  // Check current state ID at offset +0xE8
  if (*(int *)(thisPtr + 0xE8) == 2) {
    // State 2: MoveUp - call some function with string "MoveUp" and data ref
    FUN_005a04a0("MoveUp", 0, &DAT_00d88e88, 0);
  }
  else if (*(int *)(thisPtr + 0xE8) == 3) {
    // State 3: Perform action via vtable at +0x84, method at index 100 (0x64)
    // Pass sub-object at +0x128 and parameter at +0x154
    (**(code **)(*(int *)(thisPtr + 0x84) + 100))(thisPtr + 0x128, *(undefined4 *)(thisPtr + 0x154));
    return;
  }
  return;
}