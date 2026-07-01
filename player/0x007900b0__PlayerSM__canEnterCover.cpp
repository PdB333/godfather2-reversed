// FUNC_NAME: PlayerSM::canEnterCover
undefined4 __fastcall PlayerSM::canEnterCover(int this)
{
  // Check if the player state is in a valid range (state > 2)
  // +0xD0 likely stores the current state index or a state-related value
  // +0xB0 stores a sub-state or action mode (value 3 indicates a specific mode)
  // +0x5C is a bitfield of flags; bit 2 (mask 0x4) and bit 6 (mask 0x40) must be clear
  if ((((2 < *(int *)(this + 0xd0)) && (*(int *)(this + 0xb0) == 3)) &&
      ((*(uint *)(this + 0x5c) >> 2 & 1) == 0)) && ((*(uint *)(this + 0x5c) >> 6 & 1) == 0)) {
    return 1;
  }
  return 0;
}