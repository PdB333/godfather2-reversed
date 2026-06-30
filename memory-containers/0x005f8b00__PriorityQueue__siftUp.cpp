// FUNC_NAME: PriorityQueue::siftUp
void __fastcall PriorityQueue::siftUp(int param_1)
{
  float *pfVar1;
  float fVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  int unaff_ESI;
  
  // param_1 is the index of the element to sift up (1-based)
  if (1 < param_1) {
    do {
      iVar3 = *(int *)(unaff_ESI + 8); // +0x8: pointer to array of {value, priority} pairs
      iVar6 = param_1 / 2;             // parent index
      fVar2 = *(float *)(iVar3 + 4 + iVar6 * 8); // parent priority (second float in pair)
      pfVar1 = (float *)(iVar3 + 4 + param_1 * 8); // current node priority
      if (fVar2 < *pfVar1 || fVar2 == *pfVar1) {
        return; // heap property satisfied (min-heap: parent <= child)
      }
      // Swap the two elements (both value and priority)
      uVar4 = *(undefined4 *)(iVar3 + param_1 * 8);       // current node value
      uVar5 = *(undefined4 *)(iVar3 + 4 + param_1 * 8);   // current node priority
      *(undefined4 *)(iVar3 + param_1 * 8) = *(undefined4 *)(iVar3 + iVar6 * 8);       // parent value -> current
      *(undefined4 *)(iVar3 + 4 + param_1 * 8) = *(undefined4 *)(iVar3 + 4 + iVar6 * 8); // parent priority -> current
      iVar3 = *(int *)(unaff_ESI + 8);
      *(undefined4 *)(iVar3 + iVar6 * 8) = uVar4;           // current value -> parent
      *(undefined4 *)(iVar3 + 4 + iVar6 * 8) = uVar5;       // current priority -> parent
      param_1 = iVar6; // move up to parent index
    } while (1 < iVar6);
  }
  return;
}