// FUNC_NAME: PlayerF2FSM::canEnterFiringMode

bool __thiscall PlayerF2FSM::canEnterFiringMode(int this)
{
  int ctx;
  
  // +0x74: pointer to a behavior/state context block
  // The check likely tests if the player is in a state that permits firing mode entry
  if ((*(byte *)(*(int *)(this + 0x74) + 4) & 4) != 0) {
    ctx = FUN_007ab160(); // likely gets some global game state or player controller
    if (((*(byte *)(ctx + 4) & 4) != 0) &&
       ((DAT_0112a838 == 0 || (*(int *)(DAT_0112a838 + 0x5c) == 0)))) {
      return true;
    }
  }
  return false;
}