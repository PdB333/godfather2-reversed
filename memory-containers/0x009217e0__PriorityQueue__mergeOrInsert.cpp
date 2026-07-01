// FUNC_NAME: PriorityQueue::mergeOrInsert
void PriorityQueue::mergeOrInsert(int *this)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  int local_c;
  uint local_8;
  undefined4 local_4;
  
  piVar5 = this;
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  FUN_00892130(&local_c); // likely a temporary list/array allocation
  this[1] = 0; // count = 0
  FUN_009c8f10(*this); // free existing data
  *this = 0; // data pointer = null
  this[2] = 0; // capacity = 0
  this = (int *)0x0;
  if (local_8 != 0) {
    do {
      bVar4 = false;
      uVar7 = 0;
      do {
        if ((uint)piVar5[1] <= uVar7) {
          if (!bVar4) {
            iVar6 = piVar5[2];
            iVar2 = *(int *)(local_c + (int)this * 4); // item from temp list
            iVar3 = *(int *)(iVar2 + 0x174); // priority value at +0x174
            if (piVar5[1] == iVar6) {
              if (iVar6 == 0) {
                iVar6 = 1;
              }
              else {
                iVar6 = iVar6 * 2;
              }
              FUN_00920b90(iVar6); // reallocate/resize data array
            }
            piVar1 = (int *)(*piVar5 + piVar5[1] * 8); // slot for new entry (8 bytes per entry)
            piVar5[1] = piVar5[1] + 1;
            if (piVar1 != (int *)0x0) {
              *piVar1 = iVar2; // store item pointer
              piVar1[1] = iVar3; // store priority
            }
          }
          break;
        }
        iVar6 = *(int *)(local_c + (int)this * 4);
        if (*(int *)(iVar6 + 0x7c) == *(int *)(*(int *)(*piVar5 + uVar7 * 8) + 0x7c)) {
          // matching key at +0x7c, merge priority
          piVar1 = (int *)(*piVar5 + uVar7 * 8 + 4);
          *piVar1 = *piVar1 + *(int *)(iVar6 + 0x174);
          bVar4 = true;
        }
        uVar7 = uVar7 + 1;
      } while (!bVar4);
      this = (int *)((int)this + 1);
    } while (this < local_8);
  }
  if (local_c != 0) {
    FUN_009c8f10(local_c); // free temp list
  }
  return;
}