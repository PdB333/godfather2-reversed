// FUNC_NAME: CoroutineManager::yieldOrResume
int CoroutineManager::yieldOrResume(int param_1)
{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  
  piVar1 = *(int **)(param_1 + 0xc); // +0x0C: current coroutine pointer
  if ((((*(int **)(param_1 + 8) <= piVar1) || (piVar1 == (int *)0x0)) || (*piVar1 != 8)) ||
     (piVar1[1] == 0)) {
    FUN_00627a20(param_1,1,"coroutine expected"); // assert or error handler
  }
  iVar3 = FUN_0062f5c0(param_1); // evaluate coroutine condition
  puVar2 = *(undefined4 **)(param_1 + 8); // +0x08: stack pointer
  *puVar2 = 1; // push true
  if (-1 < iVar3) {
    puVar2[1] = 1; // push true
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8; // advance stack
    FUN_00625670(); // yield or schedule next
    return iVar3 + 1; // return resume value
  }
  puVar2[1] = 0; // push false
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8; // advance stack
  puVar2 = *(undefined4 **)(param_1 + 8); // get new stack top
  for (puVar4 = puVar2; puVar2 + -4 < puVar4; puVar4 = puVar4 + -2) {
    *puVar4 = puVar4[-2]; // shift stack entries down
    puVar4[1] = puVar4[-1];
  }
  puVar4 = *(undefined4 **)(param_1 + 8); // get stack top again
  puVar2[-4] = *puVar4; // copy top entry to earlier position
  puVar2[-3] = puVar4[1];
  return 2; // return yield value
}