// FUNC_NAME: StringListSelector::cycleToSelectedItem
undefined4 __thiscall StringListSelector::cycleToSelectedItem(int this, char *outBuffer, char *key)
{
  char *src;
  char cCompareResult;
  uint uKeyIndex;
  int iNextIndex;
  char *nextItem;
  char defaultBuffer [188];
  
  if (*(int *)(this + 0xc) != 0) {
    if (*(int *)(this + 0xc) == 1) {
      src = (char *)**(int **)(this + 8); // +0x8: array of pointers to items
      goto LAB_0082e5c5;
    }
    uKeyIndex = findIndexForKey(key); // FUN_0082c1b0 - returns 0xFFFFFFFF if not found
    if (uKeyIndex != 0xffffffff) {
      *(int *)(this + 4) = uKeyIndex; // +0x4: m_currentIndex
      if (uKeyIndex < *(int *)(this + 0xc) - 1U) { // +0xc: m_count
        iNextIndex = uKeyIndex + 1;
      }
      else {
        iNextIndex = 0; // wrap around
      }
      nextItem = *(char **)(*(int *)(this + 8) + iNextIndex * 4);
      src = *(char **)(*(int *)(this + 8) + uKeyIndex * 4);
      cCompareResult = stringCompare(key, nextItem + 4); // FUN_00835a00 - compare with next item's name (offset +4)
      if (cCompareResult != '\0') {
        src = nextItem; // if key matches next item's name, stay on current item? Actually this sets src to nextItem? Wait, it was already nextItem. Let me re-read decompiled: cVar2 = compare(param_3, puVar5+4). If zero? Actually if cVar2 != 0, then puVar5 = puVar1. So if compare returns non-zero (true), use current item (puVar1). So "remain on current" if next item's name matches key.
        // But the decompiled says: if (cVar2 != '\0') { puVar5 = puVar1; } so src = currentItem
        src = src; // make it clear
      }
      goto LAB_0082e5c5;
    }
  }
  getDefaultString(); // FUN_008297a0 - maybe returns pointer to empty string?
  src = defaultBuffer;
LAB_0082e5c5:
  stringCopy(outBuffer, src); // FUN_0081fac0
  return outBuffer;
}