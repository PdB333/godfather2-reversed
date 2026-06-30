// FUNC_NAME: HashTable::findNode
int __fastcall HashTable::findNode(int thisPtr, int *params)
{
  int iVar1;
  float fVar2;
  uint uVar3;
  
  *(int *)(thisPtr + 0x1034) = *(int *)(thisPtr + 0x1034) + 1; // +0x1034: totalLookups
  uVar3 = DAT_00e44680; // mask for float-to-int conversion
  fVar2 = DAT_00e2e780; // epsilon for float comparison
  iVar1 = *(int *)(thisPtr + 0x30 + params[1] * 4); // +0x30: hashTableBuckets array, params[1] = bucket index
  while( true ) {
    if (iVar1 == 0) {
      *(int *)(thisPtr + 0x103c) = *(int *)(thisPtr + 0x103c) + 1; // +0x103c: failedLookups
      return 0;
    }
    if ((((*params == *(int *)(iVar1 + 8)) && // +0x08: node key (int)
         ((float)((uint)((float)params[2] - *(float *)(iVar1 + 0x10)) & uVar3) < fVar2)) && // +0x10: node float value, compare with epsilon
        (params[3] == *(int *)(iVar1 + 0x14))) && // +0x14: node extra int 1
        (params[4] == *(int *)(iVar1 + 0x18))) break; // +0x18: node extra int 2
    *(int *)(thisPtr + 0x1040) = *(int *)(thisPtr + 0x1040) + 1; // +0x1040: collisionChecks
    iVar1 = *(int *)(iVar1 + 0x30); // +0x30: next node in chain
  }
  *(int *)(thisPtr + 0x1038) = *(int *)(thisPtr + 0x1038) + 1; // +0x1038: successfulLookups
  return iVar1;
}