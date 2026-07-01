// FUNC_NAME: InternalList::removeRange
void __thiscall InternalList::removeRange(int *list, undefined4 *begin, undefined4 *end)
{
  uint uVar1;
  undefined4 *src;
  undefined4 *dst;
  
  if ((begin != (undefined4 *)0x0) && (begin < end)) {
    do {
      // Calculate pointer to end of list data area: listPtr + count * elementSize (0xC = 12 bytes)
      src = (undefined4 *)(*list + -0xc + list[1] * 0xc);
      if (begin < src) {
        // Number of elements to shift (src - begin) / 12 * 4 bytes per dword
        uVar1 = ((uint)((int)src + (-1 - (int)begin)) / 0xc + 1) * 0xc >> 2;
        dst = begin + 3; // Skip past current element (3 dwords = 12 bytes)
        src = begin;
        // Shift remaining elements left by one element position
        for (; uVar1 != 0; uVar1 = uVar1 - 1) {
          *src = *dst;
          dst = dst + 1;
          src = src + 1;
        }
      }
      // Decrement element count
      list[1] = list[1] + -1;
      begin = begin + 3; // Move to next element (12 bytes = 3 dwords)
    } while (begin != end);
  }
  return;
}