// FUNC_NAME: GameplayDebugger::resetOrUpdateStats
void __thiscall GameplayDebugger::resetOrUpdateStats(GameplayDebugger *this, undefined4 param_2)
{
  code *pcVar1;
  int iVar2;
  
  // Call some function with param_2 (likely a flag or timer)
  (**(code **)(this[0x9ab] + 4))(param_2);
  
  // Set screen/display mode to 0xF (fullscreen?), clear all stat slots
  (**(code **)(this[0x9b1] + 4))(0xf);
  
  // Reset all stat entries (24 total, likely a stat buffer or display counters)
  // Offsets: +0x9b4 to +0x9cd each containing some float/int value
  this[0x9b4] = 0;  // +0x26D0 - stat slot 0
  this[0x9b5] = 0;  // +0x26D4 - stat slot 1
  
  pcVar1 = *(code **)(*this + 0x234);  // vtable index 0x234/4 = 0x8D
  
  this[0x9be] = 0;  // +0x26F8 - stat slot 8
  this[0x9b6] = 0;  // +0x26D8 - stat slot 2
  this[0x9c6] = 0;  // +0x2718 - stat slot 16
  this[0x9bf] = 0;  // +0x26FC - stat slot 9
  this[0x9b7] = 0;  // +0x26DC - stat slot 3
  this[0x9c7] = 0;  // +0x271C - stat slot 17
  this[0x9c0] = 0;  // +0x2700 - stat slot 10
  this[0x9b8] = 0;  // +0x26E0 - stat slot 4
  this[0x9c8] = 0;  // +0x2720 - stat slot 18
  this[0x9c1] = 0;  // +0x2704 - stat slot 11
  this[0x9b9] = 0;  // +0x26E4 - stat slot 5
  this[0x9c9] = 0;  // +0x2724 - stat slot 19
  this[0x9c2] = 0;  // +0x2708 - stat slot 12
  this[0x9ba] = 0;  // +0x26E8 - stat slot 6
  this[0x9ca] = 0;  // +0x2728 - stat slot 20
  this[0x9c3] = 0;  // +0x270C - stat slot 13
  this[0x9bb] = 0;  // +0x26EC - stat slot 7
  this[0x9cb] = 0;  // +0x272C - stat slot 21
  this[0x9c4] = 0;  // +0x2710 - stat slot 14
  this[0x9bc] = 0;  // +0x26F0 - stat slot 8
  this[0x9cc] = 0;  // +0x2730 - stat slot 22
  this[0x9c5] = 0;  // +0x2714 - stat slot 15
  this[0x9bd] = 0;  // +0x26F4 - stat slot 9
  this[0x9cd] = 0;  // +0x2734 - stat slot 23
  
  // Call vtable function at index 0x8D (0x234/4) with (0,1) - likely begin/end batch update
  (*pcVar1)(0,1);
  
  // Switch to context 1 (probably rendering context)
  FUN_007f6420(1);
  
  // If some global object (DAT_01223484+0xC) is null, call another vtable function
  if (*(int *)(DAT_01223484 + 0xc) == 0) {
    (**(code **)(*this + 0x260))();  // vtable index 0x98 - probably setupDebugRendering
  }
  
  // Call vtable function at index 0xA6 (0x298/4) with param 0
  (**(code **)(*this + 0x298))(0);
  
  // Switch to context 0x54 (84 decimal - debug rendering context?)
  FUN_007f6420(0x54);
  
  // Check if memory manager or buffer exists
  iVar2 = FUN_0043b870(DAT_01130950);
  if ((iVar2 != 0) && (*(int *)(iVar2 + 0x20) != 0)) {
    // Clear/update some debug display
    FUN_00998270();
  }
  
  // Call final vtable function at index 0x3F (0xFC/4) - likely flush or finalize
  (**(code **)(*this + 0xfc))();
}