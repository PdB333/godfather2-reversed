// FUNC_NAME: PriorityQueue::popNext
int __fastcall PriorityQueue::popNext(int param_1, int *queue)
{
  int *current;
  int *next;
  int result;
  int *entry;
  int priority;
  
  current = (int *)queue[1];  // +0x04: current read pointer
  next = (int *)queue[2];     // +0x08: current write pointer
  
  if (current == (int *)0x0) {
LAB_00588039:
    if (next == (int *)0x0) {
      return 0;
    }
    result = *next;
    next = next + 1;
    queue[2] = (int)next;
    if (next < (int *)queue[3]) {  // +0x0C: end pointer
      entry = (int *)*next;
      // Check if entry has a priority override flag (bit 0x20 at offset +0x0B)
      if (((*(byte *)(entry + 0xb) & 0x20) == 0) || (*entry < 2)) {
        priority = entry[5];  // +0x14: default priority field
      }
      else {
        priority = entry[7];  // +0x1C: override priority field
      }
      if (priority == *queue) {  // +0x00: target priority
        return result;
      }
    }
    queue[2] = 0;
    return result;
  }
  
  if (next != (int *)0x0) {
    // Compare priorities of current and next entries
    entry = (int *)*current;
    if (((*(byte *)(entry + 0xb) & 0x20) == 0) || (*entry < 4)) {
      priority = 0;
    }
    else {
      priority = entry[5];  // +0x14
    }
    entry = (int *)*next;
    if (((*(byte *)(entry + 0xb) & 0x20) == 0) || (*entry < 4)) {
      int nextPriority = 0;
    }
    else {
      int nextPriority = entry[5];  // +0x14
    }
    if (nextPriority < priority) goto LAB_00588039;
  }
  
  result = *current;
  current = current + 1;
  queue[1] = (int)current;
  if (current < (int *)queue[3]) {  // +0x0C: end pointer
    entry = (int *)*current;
    if (((*(byte *)(entry + 0xb) & 0x20) == 0) || (*entry < 2)) {
      priority = entry[5];  // +0x14
    }
    else {
      priority = entry[7];  // +0x1C
    }
    if (priority == -1) {
      return result;
    }
  }
  queue[1] = 0;
  return result;
}