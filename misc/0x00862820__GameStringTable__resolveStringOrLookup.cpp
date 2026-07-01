// FUNC_NAME: GameStringTable::resolveStringOrLookup
undefined1 GameStringTable::resolveStringOrLookup(int stringA, int stringB, int poolA, int poolB, undefined4 *key, undefined4 defaultString)
{
  undefined1 result;
  int index;
  int localBuffer[3];
  
  result = 0;
  if (stringA == 0) {
    return 0;
  }
  if (((stringB != 0) && (poolA != 0)) && (poolB != 0)) {
    if (stringA == poolA) {
      // Same pool — direct lookup by stringB in poolB
      index = FUN_005f5ec0(stringB, poolB);  // findStringInPool
      if (index != 0) {
        // +0x8: offset to string data in pool entry
        result = FUN_005fd340(*(undefined2 *)(index + 8), *key, defaultString);
        return result;
      }
    }
    else {
      // Different pools — need to remap
      FUN_005f5c20(poolA, poolB);  // remapPool
      index = FUN_005f5f20(stringB, localBuffer);  // findStringInRemappedPool
      result = 0;
      if (index != 0) {
        // +0x8: offset to string data in pool entry
        result = FUN_005fd340(*(undefined2 *)(index + 8), *key, defaultString);
      }
      if (localBuffer[0] != 0) {
        FUN_004daf90(localBuffer);  // freeRemappedBuffer
      }
    }
  }
  return result;
}