// FUNC_NAME: StreamManager::allocateStreamSlot
undefined4 StreamManager::allocateStreamSlot(uint streamId, uint flags, int priority, undefined8 *outSlot)
{
  byte *pbVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  LPCRITICAL_SECTION lpCriticalSection;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  undefined8 uVar9;
  
  _memset(outSlot, 0, 0x48); // Clear output slot structure (72 bytes)
  
  if (streamId < 0x1000) {
    iVar4 = streamId * 0x38; // 56 bytes per stream entry
    pbVar1 = &gStreamTable + iVar4; // +0x0: stream state byte
    if ((((pbVar1 != (byte *)0x0) && (bVar2 = *pbVar1, 1 < bVar2)) &&
        (((flags & 1) == 0 || (2 < bVar2)))) &&
       ((((flags & 8) != 0 || (bVar2 != 5)) && (bVar2 != 4)))) {
      // Stream is in valid state for allocation
      FUN_006064b0(streamId, flags & 2); // Mark stream as in-use
      
      // Copy stream header data (8 bytes at +0x0, 8 bytes at +0x8, 4 bytes at +0x10)
      *outSlot = *(undefined8 *)pbVar1;
      outSlot[1] = *(undefined8 *)(&gStreamTable + iVar4 + 8);
      *(undefined4 *)(outSlot + 2) = *(undefined4 *)(&gStreamTable + iVar4 + 16);
      
      // Set priority
      *(int *)((int)outSlot + 0x1c) = priority;
      
      // Check if priority should be overridden from global table
      if (((&gStreamTable + iVar4 + 4) & 2) != 0) {
        *(undefined4 *)((int)outSlot + 0x1c) = (&gPriorityOverrideTable)[priority];
      }
      
      FUN_006066e0(*(undefined2 *)((int)outSlot + 0x1c)); // Validate priority
      
      uVar3 = *(ushort *)((int)outSlot + 4); // Sample rate from stream header
      uVar8 = (uint)*(ushort *)((int)outSlot + 2); // Channels from stream header
      
      // Calculate buffer sizes
      uVar5 = FUN_0061a960(uVar8); // Get buffer size for channels
      *(undefined4 *)((int)outSlot + 0x24) = uVar5; // Output buffer size
      
      uVar5 = FUN_0061a960(uVar8); // Get buffer size for channels (again)
      *(undefined4 *)(outSlot + 4) = uVar5; // Input buffer size
      
      uVar5 = FUN_0061a960(1); // Get buffer size for mono
      *(undefined4 *)(outSlot + 6) = uVar5; // Mono buffer size
      
      uVar6 = FUN_0061a8f0(); // Get audio frame size
      *(uint *)((int)outSlot + 0x34) = uVar6; // Frame size
      
      uVar7 = FUN_0061a920(); // Get sample block size
      *(uint *)(outSlot + 7) = uVar7; // Block size
      
      *(uint *)((int)outSlot + 0x14) = streamId; // Store stream ID
      
      // Calculate number of frames and blocks
      *(uint *)((int)outSlot + 0x3c) = ((uVar6 - 1) + uVar8) / uVar6; // Frame count
      *(uint *)(outSlot + 3) = flags; // Store flags
      *(uint *)(outSlot + 8) = ((uVar7 - 1) + (uint)uVar3) / uVar7; // Block count
      
      // Check if stream should be freed
      if (((&gStreamTable + iVar4 + 4) & 8) == 0) {
        uVar6 = FUN_00618a70(); // Check if stream should be freed
      }
      else {
        uVar6 = 0;
      }
      
      lpCriticalSection = gStreamCriticalSection;
      if ((uVar6 & 1) != 0) {
        if (*pbVar1 != 5) {
          // Free the stream slot
          streamId = streamId >> 6;
          EnterCriticalSection(gStreamCriticalSection);
          LeaveCriticalSection(lpCriticalSection);
          uVar9 = __allshl(); // Shift left for bitmask
          
          // Clear bit in stream allocation bitmap
          (&gStreamAllocationBitmap)[streamId * 2] = 
               (&gStreamAllocationBitmap)[streamId * 2] & ~(uint)uVar9;
          (&gStreamAllocationBitmap)[streamId * 2 + 1] =
               (&gStreamAllocationBitmap)[streamId * 2 + 1] & ~(uint)((ulonglong)uVar9 >> 0x20);
          
          // Update highest allocated stream index
          if ((streamId == gHighestStreamIndex) &&
             ((&gStreamAllocationBitmap)[streamId * 2] == 0 && 
              (&gStreamAllocationBitmap)[streamId * 2 + 1] == 0)) {
            gHighestStreamIndex = gHighestStreamIndex + 1;
          }
          
          *pbVar1 = 4; // Mark stream as free
        }
        return 1; // Success, stream was freed
      }
    }
  }
  return 0; // Failed to allocate
}