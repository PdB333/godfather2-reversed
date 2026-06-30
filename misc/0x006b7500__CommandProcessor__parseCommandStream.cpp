// FUNC_NAME: CommandProcessor::parseCommandStream
void CommandProcessor::parseCommandStream(void* stream)
{
  char isDone;
  int element;

  // Check if flags indicate a negative state (e.g., not initialized or invalid)
  if (*(int*)(this + 0x290) < 0) {
    // Open stream from memory or similar source?
    FUN_008b9590(stream);
  } else {
    // Open stream from file or buffer?
    FUN_008bb320(stream);
  }

  // Begin iteration with a magic identifier (maybe for stream corruption check?)
  FUN_0043aff0(stream, 0x6a8acf44);
  isDone = FUN_0043b120();  // Check if iteration complete
  while (isDone == '\0') {
    element = FUN_0043b210();  // Get current element pointer
    int elementType = FUN_0043ab70();  // Get element type (0 or 1)
    if (elementType == 0) {
      if (*(int*)(this + 0x290) < 0) {
        element = FUN_0043b210();  // Re-fetch element pointer? Maybe for type0?
        // Handle element data at offset +8 from element pointer
        FUN_006b7240(*(undefined4*)(element + 8), *(undefined4*)(element + 8));
      }
    } else if (elementType == 1) {
      element = FUN_0043b210();  // Get element pointer again for type 1
      // OR byte from element+8 into flags
      *(uint*)(this + 0x290) = *(uint*)(this + 0x290) | (uint)*(byte*)(element + 8);
    }
    FUN_0043b1a0();  // Advance to next element
    isDone = FUN_0043b120();
  }
  return;
}