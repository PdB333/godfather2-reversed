// FUNC_NAME: ControllerManager::handleDeviceMessage
void __thiscall ControllerManager::handleDeviceMessage(int thisData, int* message)
{
  // thisData points to a member data block (relative to base object)
  // baseObject is at thisData - 0x3c
  // Base object's vtable at offset 0x248 is a callback/notification

  int* baseObject = *(int**)(thisData - 0x3c);

  // Check message type for specific notification
  if (DAT_012067dc == *message) {
    // Call virtual function at vtable slot 0x248 (0x248 / 4 = 146)
    (*(code**)(*baseObject + 0x248))();
  }

  // Process the message (e.g., parse or propagate)
  FUN_00542aa0(message);

  // If message indicates a specific event (e.g., device disconnected)
  if (*message == DAT_0120e93c) {
    // Only reset if a device was previously active (flag at +0x444)
    if (*(int*)(thisData + 0x444) != 0) {
      // Loop over 4 controller slots
      int* slotData = (int*)(thisData + 0x388); // Start of 4 data blocks, each 44 bytes? (0x2c)
      uint32* flags = (uint32*)(thisData + 0x368); // 4 DWORD flags

      // Loop four times (for slots 0..3)
      for (int i = 0; i < 4; i++) {
        // If this slot's flag has bit 1 clear (not active/connected)
        if ((flags[i] & 2) == 0) {
          // Reset the entire 44-byte block to zero, except element at +8 (DAT_00e2b1a4)
          void* slotBlock = (void*)(slotData + i * 11); // Each block is 44 bytes = 11 ints
          // Write zero to all fields (offsets -4 to +40 relative to slotBlock start)
          // Actually careful: the decompiler wrote with indices [-1..10] relative to puVar4,
          // where puVar4 initially points to slotData[i] (base of block).
          // So we need to zero out ranges:
          // [slotBlock-4, slotBlock+40] but excluding slotBlock+8 which gets DAT_00e2b1a4.
          // Since slotBlock is 4-byte aligned, we can zero from slotBlock-4 to slotBlock+40.
          // But the writes are to specific words. Let's mimic the exact pattern:
          // puVar4[-1] = 0; // at offset -4
          // puVar4[0] = 0;  // offset 0
          // puVar4[1] = 0;  // offset 4
          // puVar4[2] = DAT_00e2b1a4; // offset 8
          // puVar4[3] = 0; // offset 12
          // puVar4[4] = 0; // offset 16
          // puVar4[5] = 0; // offset 20
          // puVar4[6] = 0; // offset 24
          // puVar4[7] = 0; // offset 28
          // puVar4[8] = 0; // offset 32
          // puVar4[9] = 0; // offset 36
          // puVar4[10] = 0; // offset 40
          // So effectively zero 44 bytes but set word at +8 to a global constant.
          // And note that the loop increments puVar4 by 0xC (12) in the decompiled,
          // but that would cause overlap. Likely the increment is actually 0x2C (44).
          // So we assume each block is 44 bytes.

          int* blockWords = (int*)slotBlock;
          blockWords[-1] = 0; // at blockStart - 4
          blockWords[0] = 0;
          blockWords[1] = 0;
          blockWords[2] = DAT_00e2b1a4; // Some global value (e.g., 0xFFFFFFFF or constant)
          blockWords[3] = 0;
          blockWords[4] = 0;
          blockWords[5] = 0;
          blockWords[6] = 0;
          blockWords[7] = 0;
          blockWords[8] = 0;
          blockWords[9] = 0;
          blockWords[10] = 0;
          // blockWords[   -1] gives offset -4, [0]=0, [1]=4, [2]=8, [3]=12, [4]=16, [5]=20, [6]=24, [7]=28, [8]=32, [9]=36, [10]=40
          // This covers 44 bytes.
          // Note: Writing to blockWords[-1] may affect the end of previous block or a preceding field.
          // In the struct, that might be intentional (e.g., a previous member).

          // If there is a global device pointer at thisData+0x1dc (non-zero), call cleanup
          bool hasDevice = *(int*)(thisData + 0x1dc) != 0;
          if (hasDevice) {
            FUN_00572ac0(); // Some cleanup for the slot
          }
          // Update the active flag at thisData+0x444 (0 or 1)
          *(uint32*)(thisData + 0x444) = (uint32)hasDevice;
        }
        // Advance flags pointer (4 bytes per flag) - but flags is incremented by 4 in decompiled
        // flags++; // Actually pbVar2 += 4; so we just use index i.
      }
    }
    // Clear the device active flag at thisData+0x444
    *(int*)(thisData + 0x444) = 0;
  }
  return;
}