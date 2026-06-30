// FUNC_NAME: Player::handleSomeInputOrState
char __fastcall Player::handleSomeInputOrState(int thisPtr)
{
  char result;
  char isSomethingActive;

  isSomethingActive = FUN_00474730(); // Check some global state (e.g., menu, cutscene)
  if (isSomethingActive != '\0') {
    result = FUN_006a8b50(thisPtr + 0x140); // Check player-specific state at +0x140 (e.g., cover, aiming)
    if (result != '\0') {
      FUN_005e2c20(*(undefined4 *)(thisPtr + 0xe8)); // Perform action on object at +0xe8 (e.g., weapon, interactable)
      return isSomethingActive;
    }
    FUN_005e2c60(*(undefined4 *)(thisPtr + 0xe8), 4); // Set state/flag 4 on object at +0xe8
  }
  return isSomethingActive;
}