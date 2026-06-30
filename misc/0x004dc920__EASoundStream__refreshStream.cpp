// FUNC_NAME: EASoundStream::refreshStream
undefined4* EASoundStream::refreshStream(undefined4* thisStruct)

{
  short sVar1;
  uint uVar2;
  uint* in_EAX;
  short* psVar3;
  uint uVar4;
  uint uVar5;
  
  // Check if stream is currently playing (likely offset +0x04)
  if (in_EAX[1] != 0) {
    // Traverse string to null terminator at DAT_00e36ef4 (likely a configuration string)
    psVar3 = &DAT_00e36ef4;
    do {
      sVar1 = *psVar3;
      psVar3 = psVar3 + 1;
    } while (sVar1 != 0);
    
    // Get current playback position
    uVar2 = *in_EAX;  // +0x00 : position counter
    uVar4 = FUN_004dc860(); // Query hardware stream position
    
    if (uVar4 != 0) {
      // Iterate to find last valid position in chain
      do {
        uVar5 = uVar4;
        uVar4 = FUN_004dc860();
      } while (uVar4 != 0);
      
      // If we have a valid position and our local position is behind, we need to seek
      if ((uVar5 != 0) && (uVar2 < uVar5)) {
        FUN_004dba00(uVar2,(int)(uVar5 - uVar2) >> 1); // Seek to midpoint
        return thisStruct;
      }
    }
  }
  
  // Stream is not playing or no valid position - reset state
  *thisStruct = 0;      // +0x00 : position counter
  thisStruct[2] = 0;    // +0x08 : new position pending / flags
  thisStruct[1] = 0;    // +0x04 : playing flag
  return thisStruct;
}