// FUNC_NAME: TimerManager::updateTimers
void __fastcall TimerManager::updateTimers(int this)
{
  float *pfVar1;
  int iVar2;
  float fVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  
  fVar3 = DAT_012067e8; // deltaTime (global frame time)
  if ((DAT_01223520 != 0) && (sVar4 = *(short *)(this + 0x14) + -1, -1 < sVar4)) {
    iVar5 = (int)sVar4;
    iVar6 = iVar5 * 0xc; // each timer entry is 12 bytes
    do {
      iVar2 = *(int *)(this + 0x10); // pointer to timer array
      *(float *)(iVar6 + 8 + iVar2) = *(float *)(iVar6 + 8 + iVar2) - fVar3; // decrement timer countdown (+8)
      iVar2 = *(int *)(this + 0x10);
      pfVar1 = (float *)(iVar6 + 8 + iVar2);
      if ((*pfVar1 <= 0.0 && *pfVar1 != 0.0) || (*(int *)(iVar6 + iVar2) == 0)) { // timer expired or callback null
        if (*(int *)(iVar6 + iVar2) != 0) { // +0: callback function pointer
          FUN_005f72f0(*(int *)(iVar6 + iVar2)); // call timer callback
        }
        FUN_0084c4e0(iVar5); // remove timer at index
      }
      sVar4 = sVar4 + -1;
      iVar5 = iVar5 + -1;
      iVar6 = iVar6 + -0xc;
    } while (-1 < sVar4);
  }
  return;
}