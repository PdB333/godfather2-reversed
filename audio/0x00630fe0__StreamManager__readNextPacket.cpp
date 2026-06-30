// FUNC_NAME: StreamManager::readNextPacket
unsigned int __thiscall StreamManager::readNextPacket(int this)
{
  int *currentPtr;
  int local_10;
  float value;
  int local_c;
  
  currentPtr = *(int **)(this + 0xc); // +0xc: current read pointer
  if (*(int **)(this + 8) <= currentPtr) // +0x8: end of buffer
    goto skip;
  if (currentPtr == (int *)0x0)
    goto skip;
  if (*currentPtr != 3) {
    if (*currentPtr != 4)
      goto skip;
    // Type 4: read from some source (e.g., compressed float)
    int result = FUN_00636850(&value);
    if (result == 0)
      goto skip;
    local_10 = 3;
    local_c = value;
    currentPtr = &local_10;
  }
  value = (float)currentPtr[1]; // Get the float value from offset 4
  if (value == DAT_00e2b05c) { // Check for sentinel value (e.g., invalid/end marker)
    while (true) {
      currentPtr = *(int **)(this + 0xc);
      if (*(int **)(this + 8) <= currentPtr || currentPtr == (int *)0x0)
        break;
      if (*currentPtr == 3)
        break;
      if (*currentPtr == 4) {
        int result = FUN_00636850(&local_10);
        if (result != 0)
          break;
      }
      // Skip packet type
      FUN_00627ac0(PTR_s_number_00e2a8a8); // Likely advance/seek function
    }
    value = 0.0f;
  }

skip:
  unsigned int *writePtr = *(unsigned int **)(this + 8);
  *writePtr = 3; // Write type 3 (float)
  double dVar4 = (double)value;
  FUN_00b9c766(); // Some float conversion or logging
  writePtr[1] = (float)dVar4;
  *(int *)(this + 8) = *(int *)(this + 8) + 8; // Advance write pointer by 8 bytes
  return 1;
}