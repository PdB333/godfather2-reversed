// FUNC_NAME: StreamManager::allocateStreamSlot
undefined4 * StreamManager::allocateStreamSlot(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  byte bVar3;
  int in_EAX;
  
  bVar3 = FUN_005f6710(); // findFreeSlotIndex() - returns 0xff if none
  if (bVar3 != 0xff) {
    // +0x24: streamSlots array pointer
    // Each slot is 0xC bytes
    piVar1 = (int *)(*(int *)(in_EAX + 0x24) + (uint)bVar3 * 0xc);
    // piVar1[0] = stream data pointer (base)
    // piVar1[2] = allocation table pointer
    // param_1 is some ID, subtract base offset, divide by 0x24 (stream block size)
    puVar2 = (undefined4 *)(piVar1[2] + ((param_1 - *(int *)(*piVar1 + 0x20)) / 0x24) * 0xc);
    *puVar2 = 0;
    puVar2[1] = 0;
    *(byte *)((int)puVar2 + 0xb) = bVar3; // store slot index in high byte
    return puVar2;
  }
  // +0x38: flags field, set error bits (0x84 = stream full + error)
  *(uint *)(in_EAX + 0x38) = *(uint *)(in_EAX + 0x38) | 0x84;
  return (undefined4 *)0x0;
}