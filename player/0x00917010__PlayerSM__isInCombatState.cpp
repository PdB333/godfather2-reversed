// FUNC_NAME: PlayerSM::isInCombatState
undefined4 __fastcall PlayerSM::isInCombatState(int this)
{
  int state;
  
  state = *(int *)(this + 0xb8); // +0xB8: current state ID
  if (((state != 10) && (state != 0xb)) && (state != 0xc)) {
    return 0;
  }
  return 1;
}