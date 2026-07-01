// FUNC_NAME: FixedSizeQueue::push
uint __thiscall FixedSizeQueue::push(int this, undefined4 *item)
{
  int head;
  undefined4 *slot;
  
  head = *(int *)(this + 0x50);
  if (head == *(int *)(this + 0x54)) {
    // Queue full, return error (lower byte cleared)
    return in_EAX & 0xffffff00;
  }
  // Advance head pointer
  *(int *)(this + 0x50) = head + 1;
  // Calculate slot address: base + head * 16 (each slot is 16 bytes)
  slot = (undefined4 *)(head * 0x10 + *(int *)(this + 0x58));
  // Copy 16-byte item into slot
  *slot = *item;
  slot[1] = item[1];
  slot[2] = item[2];
  slot[3] = item[3];
  // Return success with lower byte set to 1
  return CONCAT31((int3)((uint)slot >> 8), 1);
}