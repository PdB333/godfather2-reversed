// FUNC_NAME: quickSortRecursive
void quickSortRecursive(int* base, int* end, undefined4 param_3)
{
  int elementCount;
  int depth;
  int i;
  
  if (base != end) {
    depth = 0;
    elementCount = (end - base) >> 2; // Number of elements (assuming 4-byte elements)
    for (i = elementCount; i != 0; i = i >> 1) {
      depth = depth + 1;
    }
    // Call introspective sort with depth limit (2*depth - 2)
    FUN_0088a270(base, end, depth * 2 + -2, param_3);
    if (0x1c < elementCount) {
      // For large arrays (>28 elements), partition and recurse
      FUN_00887690(base, base + 0x70, param_3);  // Sort left partition
      FUN_008876e0(base + 0x70, end, param_3);   // Sort right partition
      return;
    }
    // For small arrays, use insertion sort
    FUN_00887690(base, end, param_3);
  }
  return;
}