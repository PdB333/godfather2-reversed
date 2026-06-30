// FUNC_NAME: ParameterSet::loadFromBinaryStream

void __thiscall ParameterSet::loadFromBinaryStream(int thisPtr, int streamHandle)
{
  float value;
  char done;
  int index;
  int basePtr;
  int entryIdx;
  double scaledVal;
  
  // Open and seek to section with given hash key
  streamOpen(streamHandle);                          // FUN_007213b0
  streamBeginSection(streamHandle, 0x5e44b539);      // FUN_0043aff0 - likely a CRC or hash
  
  done = streamIsEmpty(streamHandle);                // FUN_0043b120
  while (done == '\0') {
    basePtr = streamReadNextToken(streamHandle);     // FUN_0043b210 - returns a pointer or offset into buffer
    index = streamReadUnsignedShort(streamHandle);   // FUN_0043ab70 - returns value < 0x1c
    
    if (index < 0x1c) {
      entryIdx = index / 7;       // 0..3 (since max 27/7=3)
      value = *(float *)(basePtr + 8);  // read float from current data position
      
      switch(index % 7) {
      case 0:
        // Property 0: stored at base+0x4c + entryIdx*4
        *(float *)(thisPtr + 0x4c + entryIdx * 4) = value;
        break;
      case 1:
        // Property 1: scaled and possibly randomized
        scaledVal = (double)(value * __globalScale1 * __globalScale2); // _DAT_00d5c458 and DAT_00e445c8
        streamRandomFunc();        // FUN_00b99e20 - side effect? Debug? 
        *(float *)(thisPtr + 0x5c + entryIdx * 4) = (float)scaledVal;
        break;
      case 2:
        // Property 2: scaled and randomized as well
        scaledVal = (double)(value * __globalScale1 * __globalScale2);
        streamRandomFunc();
        *(float *)(thisPtr + 0x6c + entryIdx * 4) = (float)scaledVal;
        break;
      case 3:
        // Property 3: stored directly
        *(float *)(thisPtr + 0x7c + entryIdx * 4) = value;
        break;
      case 4:
        // Property 4
        *(float *)(thisPtr + 0x8c + entryIdx * 4) = value;
        break;
      case 5:
        // Property 5
        *(float *)(thisPtr + 0x9c + entryIdx * 4) = value;
        break;
      case 6:
        // Property 6 (index 0)
        *(float *)(thisPtr + 0x3c + entryIdx * 4) = value;
        break;
      }
    }
    streamAdvanceCursor(streamHandle);               // FUN_0043b1a0
    done = streamIsEmpty(streamHandle);
  }
  // Stream is automatically closed or handled elsewhere
}