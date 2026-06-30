// FUNC_NAME: TNLConnection::constructPacket
undefined4 TNLConnection::constructPacket(undefined4 param_1, uint param_2)
{
  LPCRITICAL_SECTION lpCriticalSection; // critical section pointer
  int iVar1; // temp variable
  undefined4 uVar2; // temp return value
  undefined4 *puVar3; // packet list node pointer
  undefined8 *puVar4; // packet data pointer
  int unaff_ESI; // this pointer (TNLConnection*)
  
  // Get critical section from offset +0x1b8
  lpCriticalSection = *(LPCRITICAL_SECTION *)(unaff_ESI + 0x1b8);
  if (lpCriticalSection != (LPCRITICAL_SECTION)0x0) {
    EnterCriticalSection(lpCriticalSection);
    // Increment lock counter (raw offset hack)
    lpCriticalSection[1].DebugInfo =
         (PRTL_CRITICAL_SECTION_DEBUG)((int)&(lpCriticalSection[1].DebugInfo)->Type + 1);
  }
  
  // Call vtable method at offset +0x18c (probably getPacketAllocator or createPacket)
  puVar3 = (undefined4 *)(**(code **)(unaff_ESI + 0x18c))();
  if (puVar3 != (undefined4 *)0x0) {
    // Check if there's already a packet at offset +0x2c (mCurrentPacket)
    puVar4 = (undefined8 *)(unaff_ESI + 0x2c);
    if (*(int *)(unaff_ESI + 0x2c) != 0) {
      // Re-call allocator to get a new packet pointer
      puVar4 = (undefined8 *)(**(code **)(unaff_ESI + 0x18c))();
    }
    if (puVar4 != (undefined8 *)0x0) {
      // Zero out packet data (40 bytes, likely PacketHeader or similar)
      *puVar4 = 0;
      puVar4[1] = 0;
      puVar4[2] = 0;
      puVar4[3] = 0;
      puVar4[4] = 0;
      // Set packet sequence number from param_1
      *(undefined4 *)puVar4 = param_1;
      // Initialize doubly linked list pointers (prev/next?)
      *(undefined8 **)(puVar4 + 2) = puVar4;
      *(undefined8 **)((int)puVar4 + 0xc) = puVar4;
      // Set flags/state fields to 0
      *(undefined4 *)(puVar4 + 4) = 0;
      *(undefined4 *)((int)puVar4 + 0x24) = 0;
      // Set low bit to indicate valid, mask with param_2
      *(uint *)((int)puVar4 + 4) = param_2 & 0xfffffffe | 1;
      
      // Link packet into connection's send/receive list at offset +0x18
      iVar1 = *(int *)(unaff_ESI + 0x18);
      *(int *)((int)puVar4 + 0x14) = iVar1;
      *(undefined4 *)(puVar4 + 3) = *(undefined4 *)(iVar1 + 0x18);
      *(undefined8 **)(iVar1 + 0x18) = puVar4;
      *(undefined8 **)(*(int *)(puVar4 + 3) + 0x14) = puVar4;
      
      // Update node with sequence number and link into list
      *puVar3 = param_1;
      puVar3[1] = puVar3[1] & 1 | param_2 & 0xfffffffe;
      uVar2 = *(undefined4 *)(unaff_ESI + 0x17c);
      puVar3[3] = puVar4;
      puVar3[2] = uVar2;
      puVar3[4] = *(undefined4 *)(puVar4 + 2);
      *(undefined4 **)(puVar4 + 2) = puVar3;
      *(undefined4 **)(puVar3[4] + 0xc) = puVar3;
      puVar3[1] = puVar3[1] & 0xfffffffe;
      
      // Call some function (maybe updateCRC or validate)
      FUN_00649490();
      
      if (lpCriticalSection != (LPCRITICAL_SECTION)0x0) {
        // Decrement lock counter
        lpCriticalSection[1].DebugInfo =
             (PRTL_CRITICAL_SECTION_DEBUG)((int)&lpCriticalSection[1].DebugInfo[-1].SpareWORD + 1);
        LeaveCriticalSection(lpCriticalSection);
      }
      return 1;
    }
    // If packet allocation failed, call error handler at vtable offset 400
    (**(code **)(unaff_ESI + 400))();
  }
  
  if (lpCriticalSection != (LPCRITICAL_SECTION)0x0) {
    lpCriticalSection[1].DebugInfo =
         (PRTL_CRITICAL_SECTION_DEBUG)((int)&lpCriticalSection[1].DebugInfo[-1].SpareWORD + 1);
    LeaveCriticalSection(lpCriticalSection);
  }
  return 0;
}