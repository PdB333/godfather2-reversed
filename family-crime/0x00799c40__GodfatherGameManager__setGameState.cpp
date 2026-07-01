// FUNC_NAME: GodfatherGameManager::setGameState
void __fastcall GodfatherGameManager::setGameState(int this)
{
  undefined4 state;
  
  state = 4;
  if (*(int *)(this + 0x1ef4) != -1) {
    state = 3;
  }
  FUN_00811f10(this, state);
  return;
}