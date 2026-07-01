// FUNC_NAME: StreamManager::processNextChunk
void __thiscall StreamManager::processNextChunk(int this, undefined4 param_2, undefined4 param_3)
{
  char cVar1;
  int iVar2;
  
  if ((*(byte *)(this + 0x118) & 1) == 0) goto LAB_00847966;
  FUN_00428420(); // likely some time/update check
  if ((char)param_2 != '\0') goto LAB_00847966;
  iVar2 = **(int **)(this + 0xfc); // current chunk pointer +0xFC
  *(int *)(this + 300) = *(int *)(this + 300) + 1; // chunk index +0x12C
  if (*(uint *)(iVar2 + 0x10c) <= *(uint *)(this + 300)) {
    iVar2 = FUN_004025a0((*(int **)(this + 0xfc))[2]); // get next chunk data
    if (iVar2 != 0) {
      FUN_00404c40(iVar2); // free/cleanup chunk
    }
    *(int *)(this + 0xfc) = *(int *)(this + 0xfc) + 0xc; // advance to next chunk
    if (*(int **)(this + 0xfc) ==
        (int *)(*(int *)(this + 0xf0) + *(int *)(this + 0xf4) * 0xc)) {
      iVar2 = 0; // reached end of chunk list
    }
    else {
      iVar2 = **(int **)(this + 0xfc); // get new current chunk
    }
    *(undefined4 *)(this + 300) = 0; // reset chunk index
    if (*(int *)(this + 0x11c) == 0) { // +0x11C likely current stream handle
LAB_00847915:
      if ((*(byte *)(this + 0x118) & 2) == 0) goto LAB_0084791e;
    }
    else {
      cVar1 = FUN_00599180(); // check if stream is still valid
      if (cVar1 == '\0') goto LAB_00847915;
LAB_0084791e:
      if (*(int *)(this + 0xfc) == *(int *)(this + 0xf0) + *(int *)(this + 0xf4) * 0xc) {
        *(uint *)(this + 0x150) = *(uint *)(this + 0x150) | 1; // set completion flag +0x150
      }
    }
    if (iVar2 == 0) {
      FUN_00846720(); // finalize stream
      if (*(int *)(this + 0x120) != 0) { // +0x120 pending callback
        FUN_004daf90((undefined4 *)(this + 0x120)); // invoke callback
        *(undefined4 *)(this + 0x120) = 0;
      }
      goto LAB_00847966;
    }
  }
  if (*(uint *)(this + 300) < *(uint *)(iVar2 + 0x10c)) {
    iVar2 = *(int *)(*(int *)(iVar2 + 0x110) + *(uint *)(this + 300) * 4); // get chunk data pointer
    *(int *)(this + 0x11c) = iVar2; // set current stream handle
    if (iVar2 != 0) {
      FUN_008473d0(this, param_3); // process chunk data
      return;
    }
  }
LAB_00847966:
  FUN_00847650(param_2, param_3); // fallback processing
  return;
}