// FUNC_NAME: SortedArray::sortIfDirty
void __fastcall SortedArray::sortIfDirty(int this)
{
  // Check if the dirty flag at +0x10 is set
  if (*(char *)(this + 0x10) != '\0') {
    // Clear the dirty flag
    *(undefined1 *)(this + 0x10) = 0;
    // If there are more than 1 elements (count at +0x8), sort the array
    if (1 < *(uint *)(this + 8)) {
      // qsort the array pointer at +0x4, with count at +0x8, element size 4, using comparator at FUN_008ca1e0
      _qsort(*(void **)(this + 4), *(uint *)(this + 8), 4, FUN_008ca1e0);
    }
  }
  return;
}