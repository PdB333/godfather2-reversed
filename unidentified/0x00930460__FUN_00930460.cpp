// FUNC_NAME: SomeClass::updateScoringState
void __fastcall updateScoringState(int thisPtr)
{
  int state = *(int *)(thisPtr + 0xe8); // +0xe8: current scoring state (1=show, 2=hide, 3=honors)
  
  if (state == 1) {
    // Transition from show to honors
    *(int *)(thisPtr + 0xe8) = 3;
    FUN_005a04a0("ShowScoring", 0, &DAT_00d88e88, 0); // Show scoring UI
    FUN_0092fec0(); // Probably reset or update scoring display
    return;
  }
  
  if (state != 2) {
    if (state == 3) {
      // Transition from honors back to show
      *(int *)(thisPtr + 0xe8) = 2;
      FUN_005a04a0("ShowHonors", 0, &DAT_00d88e88, 0); // Show honors UI
      FUN_0092e790(thisPtr + 0x140, *(int *)(thisPtr + 0x148), *(int *)(thisPtr + 0x130),
                   *(int *)(thisPtr + 0x13c)); // Update honors display with parameters
    }
    return;
  }
  
  // State is 2 (hide) - hide scoring
  FUN_009300a0(1); // Hide scoring UI
  return;
}