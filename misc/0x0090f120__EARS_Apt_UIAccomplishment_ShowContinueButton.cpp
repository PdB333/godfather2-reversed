// Xbox PDB: EARS_Apt_UIAccomplishment_ShowContinueButton
// FUNC_NAME: ContinueScreen::updateOrShow
undefined4 __fastcall ContinueScreen::updateOrShow(int *this)
{
  this[0x22] = this[0x22] - DAT_01206804; // timer decrement by frame delta
  
  if (this[0x22] < 1) {
    // Timer expired, show continue button
    (**(code **)(*this + 8))(); // VTable call, likely virtual update/render
    FUN_005a04a0("ShowContinueButton", 0, &DAT_00d83810, 0); // UI show continue button
    *(undefined1 *)((int)this + 0x8d) = 0; // continueButtonVisible = false
    
    if (*(char *)((int)DAT_01129a74 + 0x3a1) == '\0') { // +0x3a1: some flag on game manager
      *(undefined1 *)((int)this + 0x8d) = 1; // continueButtonVisible = true
      (**(code **)(*DAT_01129a74 + 0x28))(); // VTable call, likely input enable or game state change
    }
    return 2; // return code indicating transition/showing continue button
  }
  return 0; // still waiting, timer hasn't expired
}