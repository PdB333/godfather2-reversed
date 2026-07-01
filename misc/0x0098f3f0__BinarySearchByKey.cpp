// FUNC_NAME: BinarySearchByKey
int __thiscall BinarySearchByKey(int *param_1, uint *param_2)
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar1 = param_1[1]; // +0x04: count of elements in the array
  iVar2 = -1;
  iVar6 = -1;
  if (iVar1 != 0) {
    iVar4 = iVar1;
    do {
      iVar3 = iVar4 + iVar6 >> 1; // mid = (low + high) / 2
      iVar5 = iVar3;
      if (*(uint *)(*param_1 + iVar3 * 8) < *param_2) { // compare key at mid*8 offset
        iVar5 = iVar4;
        iVar6 = iVar3;
      }
      iVar4 = iVar5;
    } while (iVar6 + 1 != iVar5); // continue until low == high
    if ((iVar5 < iVar1) && (*(uint *)(*param_1 + iVar5 * 8) == *param_2)) { // check if found
      iVar2 = iVar5;
    }
  }
  return iVar2; // returns index or -1 if not found
}