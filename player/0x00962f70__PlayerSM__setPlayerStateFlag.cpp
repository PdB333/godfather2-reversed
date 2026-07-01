// FUNC_NAME: PlayerSM::setPlayerStateFlag
void __fastcall PlayerSM::setPlayerStateFlag(int this)
{
  if (*(int *)(this + 0xdc) == 4) {
    *(uint *)(this + 0x6f4) = *(uint *)(this + 0x6f4) | 0x40;
  }
  return;
}