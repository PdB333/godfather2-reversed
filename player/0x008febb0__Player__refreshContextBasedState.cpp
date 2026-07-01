// FUNC_NAME: Player::refreshContextBasedState
void __fastcall Player::refreshContextBasedState(int thisPtr)
{
  int contextState;
  
  contextState = FUN_008fe480(); // likely determineContextState()
  if (contextState != *(int *)(thisPtr + 0xdc)) { // +0xDC: m_currentContextState
    FUN_008fddc0(); // exitContextState(thisPtr)
    FUN_008fe5e0(contextState); // enterContextState(contextState)
  }
}