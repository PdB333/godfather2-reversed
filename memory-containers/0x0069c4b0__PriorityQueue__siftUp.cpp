// FUNC_NAME: PriorityQueue::siftUp
void PriorityQueue::siftUp(int* heap, int index, int heapSize, unsigned int key, int value)
{
  int parent;
  
  if (heapSize < index) {
    do {
      parent = (index + -1) / 2;
      if ((byte)key <= *(byte *)(heap + parent * 8)) break;
      *(undefined4 *)(heap + index * 8) = *(undefined4 *)(heap + parent * 8);
      *(undefined4 *)(heap + 4 + index * 8) = *(undefined4 *)(heap + 4 + parent * 8);
      index = parent;
    } while (heapSize < parent);
  }
  *(undefined4 *)(heap + index * 8) = key;
  *(undefined4 *)(heap + 4 + index * 8) = value;
  return;
}