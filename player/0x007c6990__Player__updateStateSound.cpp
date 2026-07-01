// FUNC_NAME: Player::updateStateSound
void __fastcall Player::updateStateSound(Player *this)
{
  uint stateFlags;

  // Check if bit0 at +0x128 is set (e.g., "isInVehicle" or "isActive")
  if ((this->flags & 1) != 0) {
    // Dereference pointer at +0x58 to get a substructure (e.g., vehicle component or controller manager)
    stateFlags = *(uint *)(*(int *)((char *)this + 0x58) + 0x8e0);  // +0x8e0: state bit flags

    // Check bit25 of stateFlags (e.g., "engineRunning") and then either bit2 of another uint
    // at +0x8e8 (e.g., "radioOn") OR bit9 of stateFlags (e.g., "hornPressed")
    if (((stateFlags >> 0x19 & 1) != 0) &&
       ((*(uint *)(*(int *)((char *)this + 0x58) + 0x8e8) >> 2 & 1) != 0 || ((stateFlags >> 9 & 1) != 0))) {
      // Condition met: enable/start sound event 0x1c (e.g., engine sound)
      enableSoundEvent(0x1c);
      return;
    }
  }
  // Default: disable/stop sound event 0x1c
  disableSoundEvent(0x1c);
}