// FUNC_NAME: GameManager::setGameState
void GameManager::setGameState(int state, int param_3)
{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_50 [76];
  
  cVar1 = FUN_008754b0(param_3);
  uVar2 = DAT_00e446a0;
  if (cVar1 == '\\0') {
    uVar2 = DAT_00d5f00c;
  }
  FUN_0056c040(uVar2,state,local_50);
  FUN_0056d530(local_50,param_1);
  return;
}