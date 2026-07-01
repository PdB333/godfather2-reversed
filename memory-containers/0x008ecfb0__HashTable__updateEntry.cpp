// FUNC_NAME: HashTable::updateEntry
void HashTable::updateEntry(int param_1, int param_2)
{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  
  iVar5 = -0x1e98fd1;
  iVar2 = FUN_004461c0(param_1 + 0x20, 0); // getKeyFromObject? param_1+0x20 is key field
  if (iVar2 != 0) {
    piVar3 = (int *)FUN_0045d9e0(iVar2); // getHashComponents
    iVar5 = ((*piVar3 * 0x21 + piVar3[1]) * 0x21 + piVar3[2]) * 0x21 + piVar3[3]; // hash computation
  }
  piVar3 = (int *)FUN_008ecbc0(iVar5); // getBucketByHash
  if ((piVar3 != (int *)0x0) && (piVar4 = (int *)*piVar3, piVar4 != (int *)0x0)) {
    while (piVar4[2] != param_1) { // traverse linked list looking for matching object pointer
      piVar4 = (int *)*piVar4;
      if (piVar4 == (int *)0x0) {
        return;
      }
    }
    piVar4[3] = param_2; // update value at offset +0xC
    iVar2 = piVar3[3]; // bucket's max value
    if (iVar2 == -1) {
      puVar1 = (undefined4 *)*piVar3; // first entry in bucket
      iVar2 = -1;
      while (puVar1 != (undefined4 *)0x0) {
        piVar4 = puVar1 + 3; // value field at +0xC
        puVar1 = (undefined4 *)*puVar1;
        if (iVar2 < *piVar4) {
          iVar2 = *piVar4;
        }
      }
      piVar3[3] = iVar2; // update bucket max
    }
    if (iVar2 < param_2) {
      piVar3[3] = param_2; // update bucket max to new value
      return;
    }
    piVar3[3] = -1; // reset bucket max to -1 (needs recompute)
  }
  return;
}