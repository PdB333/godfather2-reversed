// FUNC_NAME: heapSiftDown
void heapSiftDown(int heap, int startIndex, int endIndex, undefined4 param_4, undefined4 param_5)

{
  int childIndex;
  int currentIndex;
  int swapIndex;
  
  currentIndex = startIndex * 2;
  swapIndex = startIndex;
  while (childIndex = currentIndex + 2, childIndex < endIndex) {
    if (*(byte *)(heap + childIndex * 8) < *(byte *)(heap + -8 + childIndex * 8)) {
      childIndex = currentIndex + 1;
    }
    *(undefined4 *)(heap + swapIndex * 8) = *(undefined4 *)(heap + childIndex * 8);
    *(undefined4 *)(heap + 4 + swapIndex * 8) = *(undefined4 *)(heap + 4 + childIndex * 8);
    swapIndex = childIndex;
    currentIndex = childIndex * 2;
  }
  if (childIndex == endIndex) {
    *(undefined4 *)(heap + swapIndex * 8) = *(undefined4 *)(heap + -8 + endIndex * 8);
    *(undefined4 *)(heap + 4 + swapIndex * 8) = *(undefined4 *)(heap + -4 + endIndex * 8);
    swapIndex = endIndex + -1;
  }
  FUN_0069c4b0(heap,swapIndex,startIndex,param_4,param_5);
  return;
}