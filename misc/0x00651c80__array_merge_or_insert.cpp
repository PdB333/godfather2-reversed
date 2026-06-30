// FUNC_NAME: array_merge_or_insert
int array_mergeOrInsert(int destArray, int srcArray, int insertIndex, int elementSize)
{
  int result;
  
  FUN_00652520(insertIndex);
  return elementSize + ((srcArray - destArray >> 2) + (result - insertIndex >> 2)) * 4;
}