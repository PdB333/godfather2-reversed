// FUNC_NAME: ObjectPool::removeByKey
uint __thiscall ObjectPool::removeByKey(int *this, int *keyPtr)
{
  int *prevNode;
  int *currNode;
  int capacity;
  int head;
  int tail;
  int foundIndex;
  int key;
  uint result;

  result = (uint)((int)this[2] << 24) | 0x100; // high byte of head + flag

  if (this[3] != 0) {
    capacity = this[1];
    head = this[2];
    tail = head - 1 + this[3];
    if (capacity <= tail) {
      tail = tail - capacity;
    }

    foundIndex = tail;
    key = *(int *)(*this + foundIndex * 8);
    while (key != *keyPtr) {
      if (foundIndex == head) {
        return result;
      }
      foundIndex = foundIndex - 1;
      if (foundIndex < 0) {
        foundIndex = foundIndex + capacity;
      }
      key = *(int *)(*this + foundIndex * 8);
    }

    if (foundIndex != head) {
      do {
        int prevIndex = foundIndex - 1;
        if (prevIndex < 0) {
          prevIndex = prevIndex + capacity;
        }
        prevNode = (int *)(*this + prevIndex * 8);
        currNode = (int *)(*this + foundIndex * 8);
        if (currNode != prevNode) {
          int prevKey = *prevNode;
          if (*currNode != prevKey) {
            if (*currNode != 0) {
              FUN_004daf90(currNode); // release/destruct node
            }
            *currNode = prevKey;
            if (prevKey != 0) {
              currNode[1] = *(int *)(prevKey + 4); // copy next pointer from object
              *(int **)(prevKey + 4) = currNode; // update object's next to point to current node
            }
          }
        }
        foundIndex = prevIndex;
      } while (prevIndex != head);
    }

    // Advance head (remove oldest element)
    this[2] = this[2] + 1;
    if (this[1] <= this[2]) {
      this[2] = this[2] - this[1];
    }
    this[3] = this[3] - 1; // decrement count

    result = (uint)((int)this[2] << 24) | 1; // new head with success flag
  }

  return result;
}