// FUNC_NAME: SerializeTransformAndIdData
undefined4 SerializeTransformAndIdData(void)

{
  char isEnd;
  int chunkType;
  undefined4 result;
  undefined4 thisPtr; // unaff_EDI
  undefined1 *chunkData;
  int scaledX;
  int scaledY;
  int scaledZ;
  undefined1 local_c0[12];
  undefined4 local_b4;
  undefined4 local_a4;
  undefined4 local_94;
  float posX;
  float posY;
  float posZ;
  undefined4 local_84;
  
  result = 0;
  // Begin reading chunk type 0xb390b11a (likely a transform chunk)
  FUN_0043aff0(thisPtr, 0xb390b11a);
  isEnd = FUN_0043b120();
  while (isEnd == '\0') {
    FUN_0043b210();
    chunkType = FUN_0043ab70();
    if (chunkType == 1) {
      // Read transform data from chunk
      chunkData = local_c0;
      local_b4 = 0;
      local_a4 = 0;
      local_94 = 0;
      local_84 = _DAT_00d5780c;
      FUN_0043b210(chunkData);
      FUN_0043ac60(chunkData);
      // Scale floats to game units and write as integers
      scaledX = (int)(posX * DAT_00d5e288);
      scaledY = (int)(posY * DAT_00d5e288);
      scaledZ = (int)(posZ * DAT_00d5e288);
      result = FUN_004db3f0(result, &scaledX, 4);
      result = FUN_004db3f0(result, &scaledY, 4);
      result = FUN_004db3f0(result, &scaledZ, 4);
    }
    FUN_0043b1a0();
    isEnd = FUN_0043b120();
  }
  // Begin reading chunk type 0x580e3e39 (likely an ID chunk)
  FUN_0043aff0(thisPtr, 0x580e3e39);
  isEnd = FUN_0043b120();
  while (isEnd == '\0') {
    FUN_0043b210();
    chunkType = FUN_0043ab70();
    if (chunkType == 0) {
      // Read integer ID from chunk
      chunkType = FUN_0043b210();
      scaledX = *(int *)(chunkType + 8);
      result = FUN_004db3f0(result, &scaledX, 4);
    }
    FUN_0043b1a0();
    isEnd = FUN_0043b120();
  }
  return result;
}