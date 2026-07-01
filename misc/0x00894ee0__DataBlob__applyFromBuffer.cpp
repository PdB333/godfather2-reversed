//FUNC_NAME: DataBlob::applyFromBuffer
undefined4 __thiscall DataBlob::applyFromBuffer(int thisPtr, undefined4 param_2, int *buffer, uint bufferSize)
{
  uint i;
  int count;
  int propIndex;
  
  // Check if property definitions exist
  if (*(int *)(thisPtr + 0x18) != 0) {
    // Mode 1: No external buffer – copy from internal source
    if (buffer == (int *)0x0) {
      // If the "dirty" flag is set and there are properties defined
      if (((*(byte *)(thisPtr + 0x20) & 1) != 0) &&
         (i = 0, *(int *)(*(int *)(thisPtr + 0x18) + 8) != 0)) {
        count = 0;
        do {
          // Copy each property value from source (+0x1c) to destination (+0x18+0x18)
          *(undefined4 *)(*(int *)(*(int *)(thisPtr + 0x18) + 0x18) + 8 + count) =
               *(undefined4 *)(*(int *)(thisPtr + 0x1c) + i * 4);
          i = i + 1;
          count = count + 0x14; // Each property entry is 20 bytes
        } while (i < *(uint *)(*(int *)(thisPtr + 0x18) + 8));
        // Clear the filter flag
        *(undefined1 *)(thisPtr + 0x30) = 0;
        return 1;
      }
    }
    // Mode 2: External buffer – parse and apply
    else if ((3 < bufferSize) && (count = *buffer, bufferSize - 4 == count * 8 + 4)) {
      buffer = buffer + 1; // Skip count
      // If filter flag is clear, apply all properties
      if (*(char *)(thisPtr + 0x30) == '\0') {
        for (; count != 0; count = count + -1) {
          propIndex = FUN_00893470(*buffer); // Resolve property hash to index
          if (propIndex != 0) {
            FUN_00894d00(propIndex, buffer[1], 0x80000001, 0); // Set property value
          }
          buffer = buffer + 2;
        }
      }
      // If filter flag is set, only apply specific properties (e.g., "name" and "type")
      else if (count != 0) {
        do {
          propIndex = *buffer;
          if (((propIndex == 0x41b35eff) || (propIndex == 0x7589ba59)) &&
             (propIndex = FUN_00893470(propIndex), propIndex != 0)) {
            FUN_00894d00(propIndex, buffer[1], 0x80000001, 0);
          }
          buffer = buffer + 2;
          count = count + -1;
        } while (count != 0);
        // Clear the filter flag after processing
        *(undefined1 *)(thisPtr + 0x30) = 0;
        return 1;
      }
    }
  }
  // Clear filter flag and return success
  *(undefined1 *)(thisPtr + 0x30) = 0;
  return 1;
}