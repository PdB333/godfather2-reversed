// FUNC_NAME: SomeClass::findClosestValueInSortedArray
char SomeClass::findClosestValueInSortedArray(undefined4 this, float targetValue, undefined4 *outValue)
{
  int iVar1;
  int iVar2;
  char found;
  
  found = '\0';
  iVar1 = FUN_00893550(this); // Get internal data structure (likely a sorted array of pairs)
  if ((iVar1 != 0) && (iVar2 = *(int *)(iVar1 + 4), iVar2 != 0)) {
    do {
      iVar2 = iVar2 + -1;
      if (iVar2 < 0) {
        return found;
      }
      // Compare float at offset 0 in each 8-byte element (key)
      if (*(float *)(*(int *)(iVar1 + 8) + iVar2 * 8) <= targetValue) {
        found = '\x01';
        // Store the associated value at offset 4 in each 8-byte element
        *outValue = *(undefined4 *)(*(int *)(iVar1 + 8) + iVar2 * 8 + 4);
      }
    } while (found == '\0');
    return found;
  }
  return '\0';
}