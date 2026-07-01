// FUNC_NAME: PlayerSM::resetStateFlags
void __thiscall resetStateFlags(int this, char param_2)
{
  *(undefined4 *)(this + 0x5ec) = 0;  // +0x5ec: some timer or counter
  *(bool *)(this + 0x5e1) = param_2 == '\0';  // +0x5e1: flag1, set to true if param_2 is zero
  *(bool *)(this + 0x5e3) = param_2 == '\0';  // +0x5e3: flag2, set to true if param_2 is zero
  *(undefined4 *)(this + 0x5e8) = 0;  // +0x5e8: some state or timer
  return;
}