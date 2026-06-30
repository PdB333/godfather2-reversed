// FUNC_NAME: MissionManager::completeActiveObjectives
void FUN_0051b250(int this)
{
  uint *puVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int unaff_FS_OFFSET;
  
  iVar4 = 0;
  if (0 < *(short *)(this + 0x80)) { // +0x80: objectiveCount (short)
    piVar2 = *(int **)(unaff_FS_OFFSET + 0x2c); // FS segment offset, likely thread-local storage
    piVar3 = (int *)(this + 0xf4); // +0xF4: array of objective pointers (5 elements each)
    do {
      if ((*(int *)(this + 0x10) != 0) && (*piVar3 != 0)) { // +0x10: mission active flag
        puVar1 = (uint *)(*(int *)(*piVar3 + 0x10) + *(int *)(*piVar2 + 8)); // objective +0x10: status field, offset by thread-local delta
        *puVar1 = *puVar1 | 0x8000000; // set bit 27: mark objective as completed
        (**(code **)(*(int *)*piVar3 + 0x28))(); // call objective's completion callback at +0x28
      }
      iVar4 = iVar4 + 1;
      piVar3 = piVar3 + 5; // each objective entry is 5 ints wide
    } while (iVar4 < *(short *)(this + 0x80));
  }
  return;
}