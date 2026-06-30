// FUNC_NAME: EntityManager::allocateEntitySlot
uint EntityManager::allocateEntitySlot(int param_1, undefined4 param_2, int param_3)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  char cVar3;
  undefined4 *in_EAX;
  uint uVar4;
  int iVar5;
  int *piVar6;
  
  uVar2 = *in_EAX;
  uVar4 = 0;
  piVar6 = (int *)(param_1 + 0x28); // +0x28: slotUsedFlags array
  do {
    if (*piVar6 == 0) { // slot is free
      puVar1 = (undefined4 *)(uVar4 * 0x30 + 0x10 + param_1); // +0x10: slot data array (0x30 bytes each)
      if (puVar1 != (undefined4 *)0x0) {
        iVar5 = FUN_005e6100(in_EAX,uVar2,param_2); // allocate entity instance
        puVar1[4] = iVar5; // +0x10: entity pointer
        puVar1[6] = 1; // +0x18: active flag
        puVar1[7] = *(undefined4 *)(param_3 + 0xc); // +0x1c: type
        puVar1[8] = uVar2; // +0x20: some ID
        puVar1[9] = *(undefined4 *)(param_3 + 0x10); // +0x24: data
        puVar1[10] = *(undefined4 *)(param_3 + 0x14); // +0x28: more data
        puVar1[0xb] = 0; // +0x2c: flags
        *(undefined4 *)(iVar5 + 0x6c) = *(undefined4 *)(param_3 + 0x18); // entity +0x6c: field
        *(undefined4 *)(puVar1[4] + 0x70) = *(undefined4 *)(param_3 + 0x1c); // entity +0x70: field
        puVar1[2] = 0; // +0x08: some counter
        puVar1[1] = 0; // +0x04: some counter
        *puVar1 = 0; // +0x00: some counter
        puVar1[3] = DAT_00e2b1a4; // +0x0c: global value
        FUN_005dbc10(puVar1[5],uVar2); // initialize something
        if (puVar1[4] != 0) {
          _memset((void *)(puVar1[4] + 0xc),0,0x30); // clear entity data
          uVar4 = puVar1[5]; // slot index
          *(int *)(param_1 + 0x6040) = *(int *)(param_1 + 0x6040) + 1; // +0x6040: allocation counter
          uVar4 = (*(int *)(param_1 + 0x6040) << 0x10 | uVar4) ^ 0xad5c0000; // generate unique ID
          puVar1[0xb] = uVar4; // store unique ID
          FUN_005e5200(2); // notify allocation
          return uVar4;
        }
        uVar4 = puVar1[5]; // slot index
        cVar3 = FUN_005e63e0(uVar4); // check if slot is valid
        if (cVar3 != '\0') {
          iVar5 = 0;
          if (uVar4 < 0x200) { // max 512 slots
            iVar5 = uVar4 * 0x30 + 0x10 + param_1;
          }
          *(undefined4 *)(iVar5 + 0x20) = 0; // clear slot data
          *(undefined4 *)(iVar5 + 0x18) = 0;
          *(undefined4 *)(iVar5 + 0x2c) = 0;
          *(undefined4 *)(iVar5 + 0x10) = 0;
        }
      }
      return 0;
    }
    uVar4 = uVar4 + 1;
    piVar6 = piVar6 + 0xc; // advance to next slot (0xc = 3 ints per slot flag)
  } while (uVar4 < 0x200); // max 512 slots
  return 0;
}