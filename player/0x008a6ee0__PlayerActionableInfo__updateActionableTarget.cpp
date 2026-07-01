// FUNC_NAME: PlayerActionableInfo::updateActionableTarget
void __thiscall PlayerActionableInfo::updateActionableTarget(int thisPtr, int param_2)
{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  uint uVar4;
  float10 fVar5;
  undefined4 local_2c;
  undefined ***local_28;
  undefined1 local_24;
  undefined **local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if (param_2 != 0) {
    uVar4 = *(uint *)(thisPtr + 0x58); // +0x58: some timer or counter
    cVar2 = FUN_00481620(); // likely isPlayerAlive() or similar
    if ((((cVar2 != '\0') && (iVar1 = *(int *)(param_2 + 0x1ed8), iVar1 != 0)) && (iVar1 != 0x48))
       && (*(int *)(iVar1 + 0x1e8) != 0)) {
      fVar5 = (float10)FUN_00892390(); // likely getDeltaTime() or getFrameTime()
      if (((int)uVar4 < 0) &&
         ((float)fVar5 < (float)(int)((uVar4 ^ (int)uVar4 >> 0x1f) - ((int)uVar4 >> 0x1f)))) {
        uVar4 = -(int)fVar5;
      }
      FUN_008c29d0(uVar4,*(undefined4 *)(thisPtr + 0x5c)); // +0x5c: some parameter
      if (*(int *)(thisPtr + 0x60) != 0) { // +0x60: pointer to something
        uVar3 = FUN_005e3070(); // likely getCurrentTime()
        FUN_005e6550(*(undefined4 *)(thisPtr + 0x60),uVar3); // setTime or update
      }
    }
    if (((*(int *)(DAT_0112b9b4 + 0x40) != 0) && // global game manager check
        ((*(int *)(*(int *)(DAT_0112b9b4 + 0x40) + 0xd8) != 2 || // game state check
         (cVar2 = FUN_00481620(), cVar2 != '\0')))) &&
       (local_10 = *(int *)(param_2 + 0x1ef8), local_10 != -1)) { // +0x1ef8: some ID or index
      local_1c = *(undefined4 *)(thisPtr + 0x50); // +0x50: some data
      local_18 = DAT_00e54408; // global variable
      local_28 = &local_20;
      local_c = 0xffffffff;
      local_8 = 0;
      local_4 = 0;
      local_20 = &PTR_LAB_00d77a04; // vtable or function pointer table
      local_2c = DAT_0112ecfc; // global variable
      local_24 = 0;
      local_14 = uVar4;
      FUN_00408a00(&local_2c,0); // likely sendEvent or dispatchAction
    }
  }
  return;
}