// FUNC_NAME: AudioDataManager::toggleSoundBank
void __thiscall AudioDataManager::toggleSoundBank(void* this, char param_2)
{
  bool bVar1;
  int iVar2;
  int *piVar3;
  undefined1 local_10 [12];
  
  iVar2 = 0;
  if (0 < *(int *)(this + 0x78)) {
    piVar3 = *(int **)(this + 0x74);
    do {
      if (*piVar3 == 0x2004) {
        bVar1 = true;
        goto LAB_00541bdb;
      }
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 4;
    } while (iVar2 < *(int *)(this + 0x78));
  }
  bVar1 = false;
LAB_00541bdb:
  if (param_2 == '\0') {
    if (bVar1) {
      // Remove soundbank 0x2004 from loaded banks list
      FUN_009f0250(local_10,0x2004);
    }
    return;
  }
  if (!bVar1) {
    // Load soundbank 0x2004
    FUN_009f01f0(0x2004,1,0);
    return;
  }
  // Unload soundbank 0x2004
  FUN_009f0300(0x2004,1,0);
  return;
}