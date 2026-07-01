// FUNC_NAME: PlayerSM::handleInput
void __thiscall PlayerSM::handleInput(int this, undefined4 inputData)
{
  char isPaused;
  
  isPaused = FUN_00481640(); // likely GameManager::isPaused or similar
  if (isPaused != '\0') {
    FUN_0079ff90(inputData); // handleInputWhilePaused
    return;
  }
  // Check if player is in a state that blocks input (bit 0x800000 at +0x8e0)
  if ((*(uint *)(this + 0x8e0) >> 0x17 & 1) == 0) {
    isPaused = FUN_0089c630(); // likely some other pause check (e.g., cutscene)
    if (isPaused == '\0') {
      FUN_0079f4c0(inputData); // processNormalInput
      // Call virtual function at vtable+0x28 (likely updateState or similar)
      (**(code **)(*(int *)(this + 0x58) + 0x28))(0x20000);
    }
  }
  return;
}