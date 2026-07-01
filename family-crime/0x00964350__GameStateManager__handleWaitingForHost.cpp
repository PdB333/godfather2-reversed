// FUNC_NAME: GameStateManager::handleWaitingForHost
void GameStateManager::handleWaitingForHost(int param_1)
{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;

  iVar1 = DAT_01223484; // global game state manager pointer
  if ((DAT_01223484 != 0) && (*(int *)(DAT_01223484 + 0xc) != 0)) {
    // Show waiting for host message
    FUN_0096f7a0("$mp_waiting_for_host", 1); // likely showHUDMessage or similar
    FUN_008b5c70(param_1); // process pending network or input
    // Get some object pointer via virtual function call
    piVar2 = (int *)(**(code **)(**(int **)(iVar1 + 0xc) + 8))(); // Get something from game state
    uVar3 = (**(code **)(*piVar2 + 0xc))(); // Virtual function on that object
    FUN_008b5c90(uVar3); // use result
    FUN_008b5d40(); // finalize state transition
  }
  return;
}