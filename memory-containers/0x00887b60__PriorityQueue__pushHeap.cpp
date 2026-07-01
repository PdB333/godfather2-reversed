// FUNC_NAME: PriorityQueue::pushHeap
void PriorityQueue::pushHeap(int* heap, int heapSize, int newElement, int* elementPtr)
{
  int parentIdx;
  int parentValue;
  
  if (newElement <= heapSize) {
    heap[newElement] = *elementPtr;
    return;
  }
  do {
    parentIdx = (newElement - 1) >> 1;  // (newElement - 1) / 2
    parentValue = heap[parentIdx];
    // Compare priority values: element at +0x60 in the object at +0x14
    if (*(uint*)(*(int*)(*elementPtr + 0x14) + 0x60) <= *(uint*)(*(int*)(parentValue + 0x14) + 0x60))
      break;
    heap[newElement] = parentValue;
    newElement = parentIdx;
  } while (heapSize < parentIdx);
  heap[newElement] = *elementPtr;
  return;
}