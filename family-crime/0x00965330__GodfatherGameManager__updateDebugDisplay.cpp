// FUNC_NAME: GodfatherGameManager::updateDebugDisplay
void GodfatherGameManager::updateDebugDisplay(void *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 local_214;
  undefined1 local_210 [128];
  undefined1 local_190 [128];
  undefined4 local_110 [4];
  undefined4 local_100;
  
  if (DAT_0112b9b4 != 0) {
    puVar2 = (undefined4 *)(DAT_01129930 + 0x1a8);
    puVar3 = local_110;
    for (iVar1 = 0x42; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    iVar1 = FUN_00963f80(local_100);
    if (iVar1 != 0) {
      local_214 = param_1;
      FUN_004d6290(local_190,&local_214,0x80);
      FUN_004d6290(local_210,&local_214,0x80);
      FUN_00932eb0(local_190,local_210);
      return;
    }
  }
  if (DAT_01223484 != (int *)0x0) {
    (**(code **)(*DAT_01223484 + 0x98))();
    FUN_00962c70();
  }
  return;
}