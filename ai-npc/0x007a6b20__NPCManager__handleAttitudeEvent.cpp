// FUNC_NAME: NPCManager::handleAttitudeEvent
void __thiscall NPCManager::handleAttitudeEvent(int thisPtr, int eventParam)
{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  // Process the event parameter first
  FUN_004815c0(eventParam);
  if (eventParam != 0) {
    // Check bit 28-31 of offset 0x890 (some flag field)
    if ((*(uint *)(thisPtr + 0x890) >> 0x1c & 1) == 0) {
      // Check if bit 0 at offset 0x88b is set (some state flag)
      if ((*(byte *)(thisPtr + 0x88b) & 1) != 0) {
        // Allocate 0x58 bytes for some attitude/event structure
        iVar2 = FUN_009c8e50(0x58);
        if (iVar2 == 0) {
          iVar2 = 0;
        }
        else {
          // Call constructor on this - 0x58 (adjusting for potential embedded object)
          iVar2 = FUN_0079fa30(thisPtr + -0x58);
        }
        uVar1 = *(uint *)(thisPtr + 0x888);
        local_38 = CONCAT31(local_38._1_3_,1);
        // Build a complex status word with several fields
        *(ulonglong *)(iVar2 + 0x3c) = CONCAT44(2,local_38);
        *(ulonglong *)(iVar2 + 0x44) = CONCAT44(uStack_2c,uVar1 >> 0x1e) & 0xffffffff00000001;
        *(ulonglong *)(iVar2 + 0x4c) = CONCAT44(uStack_24,local_28);
        *(undefined4 *)(iVar2 + 0x38) = 6;  // Action type = 6 (likely some attitude action)
        *(undefined4 *)(iVar2 + 0x54) = local_20;
        FUN_0064ef60(iVar2);  // Queue/execute the action
      }
    }
    else {
      // Different branch for another flag state
      iVar2 = FUN_009c8e50(0x58);
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = FUN_0079fa30(thisPtr + -0x58);
      }
      uVar3 = FUN_007e0d40();  // Get some global state
      FUN_004a8f30(uVar3);     // Process it
      local_1c = CONCAT31(local_1c._1_3_,1);
      *(ulonglong *)(iVar2 + 0x3c) = CONCAT44(7,local_1c);
      *(ulonglong *)(iVar2 + 0x44) = CONCAT44(uStack_34,local_38);
      *(ulonglong *)(iVar2 + 0x4c) = CONCAT44(uStack_2c,local_30);
      *(undefined4 *)(iVar2 + 0x38) = 4;  // Action type = 4 (different action)
      *(undefined4 *)(iVar2 + 0x54) = local_28;
      FUN_0064ef60(iVar2);
    }
    // Check a flag at offset 0x30c4 (possibly "already processed" flag)
    if (*(char *)(thisPtr + 0x30c4) == '\0') {
      FUN_007a1170(eventParam);  // Continue processing the event
    }
  }
  return;
}