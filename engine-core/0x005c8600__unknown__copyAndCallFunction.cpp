// FUNC_NAME: unknown::copyAndCallFunction
void FUN_005c8600(int thisPtr, int param2, int param3, int* sourceArray)
{
  int i;
  int localBuffer[19]; // 0x4C bytes (19 * 4)
  
  // Copy 16 dwords (0x40 bytes) from source to local buffer
  for (i = 0x10; i != 0; i--) {
    localBuffer[16 - i] = *sourceArray;
    sourceArray++;
  }
  
  // Call function with thisPtr and the copied buffer
  FUN_005d1f10(thisPtr, localBuffer);
}