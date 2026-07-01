// FUNC_NAME: GodfatherGameManager::updateGameState
void __fastcall GodfatherGameManager::updateGameState(int *this)
{
  char cVar1;
  
  FUN_00983120(0,0,0);
  if (*(char *)(DAT_01223394 + 0x54) == '\0') {
    cVar1 = FUN_004035a0();
    if (cVar1 != '\0') {
                    // WARNING: Could not recover jumptable at 0x0092e316. Too many branches
                    // WARNING: Treating indirect jump as call
      (**(code **)(*this + 0x28))();
      return;
    }
  }
  FUN_00408680(&DAT_012069c4);
  return;
}