// FUNC_NAME: HudIconDisplay::checkTimeoutTimer
bool __thiscall HudIconDisplay::checkTimeoutTimer(HudIconDisplay *this)
{
  if ((*(uint *)(this + 0x50) >> 4 & 1) != 0) { // check if bit 4 of flags is set (timer active flag)
    *(int *)(this + 0x70) = *(int *)(this + 0x70) + DAT_01206804; // add delta time (+0x70 is elapsed time accumulator)
    if (*(uint *)(this + 0x70) < 0x5dc) { // 1500 ms timeout?
      return false;
    }
    // Timer expired - hide icon
    FUN_005a04a0("HideIconDisplay", 0, &DAT_00d87b2c, 0); // UnrealScript/EA script event dispatch
    *(uint *)(this + 0x50) = *(uint *)(this + 0x50) & 0xffffffe7; // clear bits 3,4,5 (reset timer active and visibility flags)
  }
  return true;
}