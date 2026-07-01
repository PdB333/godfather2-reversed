// FUNC_NAME: SortableArray::sortAndClampRanges
void __thiscall SortableArray::sortAndClampRanges(SortableArray *this, char shouldSort)
{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  if (shouldSort != '\0') {
    uVar3 = *(uint *)(*this + 4); // +0x4 element count = array header
    if (1 < uVar3) {
      _qsort(*(void **)*this, uVar3, 0x18, (_PtFuncCompare *)&LAB_00816bd0);
    }
  }
  
  // Clamp each range element's duration to not exceed the distance to next range start
  if ((1 < *(uint *)(*this + 4)) && (iVar2 = *(uint *)(*this + 4) - 1, iVar2 != 0)) {
    iVar4 = 0;
    do {
      uVar3 = *(uint *)(*(int *)*this + iVar4);       // +0x0 rangeStart of current element
      iVar1 = *(int *)*this + iVar4;
      if (uVar3 < *(uint *)(iVar1 + 0x18)) {          // +0x18 rangeStart of next element
        uVar3 = *(uint *)(iVar1 + 0x18) - uVar3;     // distance to next start
      }
      else {
        uVar3 = 0;
      }
      if (uVar3 < *(uint *)(iVar1 + 4)) {             // +0x4 duration of current element
        *(uint *)(iVar1 + 4) = uVar3;                 // clamp duration to distance
      }
      iVar4 = iVar4 + 0x18;                           // each element is 0x18 bytes
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return;
}