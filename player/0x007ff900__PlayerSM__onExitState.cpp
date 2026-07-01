// FUNC_NAME: PlayerSM::onExitState
void __thiscall PlayerSM::onExitState(int this, undefined4 param_2)
{
  // Call base class or helper to clean up state-specific data
  FUN_007ff8a0(param_2);
  
  // Check if this is not a special sentinel value (-0x3c0 = -960) and if there's a valid pointer at +0x3d4
  if ((this != -0x3c0) && (*(int *)(this + 0x3d4) != 0)) {
    // Likely stop some audio or effect (2 = some sound/effect ID)
    FUN_005512c0(2);
  }
  
  // Check bit 4 of flags at +0x8e0 (bit 4 = 0x10) - if not set, do something
  if ((*(uint *)(this + 0x8e0) >> 4 & 1) == 0) {
    // Call virtual function at vtable+0x28 with parameter 0x20 (32)
    // This is likely a method like setStateFlag or similar
    (**(code **)(*(int *)(this + 0x58) + 0x28))(0x20);
  }
  
  // Set bit 4 (0x10) in flags at +0x8e0
  *(uint *)(this + 0x8e0) = *(uint *)(this + 0x8e0) | 0x10;
  
  // Set bit 27 (0x8000000) in flags at +0x1b94
  *(uint *)(this + 0x1b94) = *(uint *)(this + 0x1b94) | 0x8000000;
  
  // If there's a valid pointer at +0x1e70, call some cleanup function
  if (*(int *)(this + 0x1e70) != 0) {
    FUN_004df600();
  }
  
  // If there's a valid pointer at +0x1e84, call the same cleanup function
  if (*(int *)(this + 0x1e84) != 0) {
    FUN_004df600();
  }
  
  // Set bits 5 and 6 (0x60) in flags at +0x970
  *(uint *)(this + 0x970) = *(uint *)(this + 0x970) | 0x60;
  
  // Call some finalization/cleanup function
  FUN_007f7e40();
  
  return;
}