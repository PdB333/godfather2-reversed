// FUNC_NAME: EventSystem::dispatchEvent
void EventSystem::dispatchEvent(uint eventId, undefined4 param_2, undefined4 *dataBlock, undefined8 *extraData)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined8 local_60;
  undefined8 local_58;
  undefined4 local_50 [19];
  
  if ((_DAT_01225e2c & 1) == 0) {
    _DAT_01225e2c = _DAT_01225e2c | 1;
    _DAT_01225e10 = &PTR_FUN_00e36cb4;
    FUN_004cfc30(0x200);  // Allocate 512 bytes for event data
    _atexit((_func_4879 *)&LAB_00d51130);  // Register cleanup
  }
  // Lookup event handler in hash table
  // DAT_01225e14 = hash table base pointer
  // DAT_01225e18 = hash table size (modulus)
  puVar1 = *(uint **)(DAT_01225e14 + (eventId % DAT_01225e18) * 4);
  do {
    if (puVar1 == (uint *)0x0) {
LAB_005d5f0d:
      uVar2 = 0;
LAB_005d5f0f:
      // Copy 16 uint32 from dataBlock into local buffer
      puVar4 = local_50;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *dataBlock;  // Copy word
        dataBlock = dataBlock + 1;
        puVar4 = puVar4 + 1;
      }
      // Copy extra 128-bit data
      local_60 = *extraData;
      local_58 = extraData[1];
      // Dispatch to registered handler
      FUN_005d2010(uVar2, param_2, local_50, &local_60);
      return;
    }
    if (*puVar1 == eventId) {
      if ((puVar1 != (uint *)0x0) && (puVar1 + 1 != (uint *)0x0)) {
        uVar2 = puVar1[1];  // Get handler ID from entry
        goto LAB_005d5f0f;
      }
      goto LAB_005d5f0d;
    }
    puVar1 = (uint *)puVar1[2];  // Walk linked list for hash collision
  } while( true );
}