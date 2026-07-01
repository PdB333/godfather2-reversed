// FUNC_NAME: InputManager::updateControllerSlots
void InputManager::updateControllerSlots(void)
{
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  undefined4 *puVar5;
  char local_448 [64];  // controller name buffer
  char local_408 [1028]; // controller data buffer (0x100 * 4 = 1024 bytes + null)
  
  // Calculate pointer to controller slot data (DAT_0113058c is slot index, 0x504 is stride, DAT_0113055c is base)
  iVar2 = DAT_0113058c * 0x504 + DAT_0113055c;
  puVar5 = (undefined4 *)(iVar2 + 0x44); // +0x44: controller data start offset
  pcVar3 = local_408;
  for (iVar4 = 0x100; iVar4 != 0; iVar4 = iVar4 + -1) {
    *(undefined4 *)pcVar3 = *puVar5;
    puVar5 = puVar5 + 1;
    pcVar3 = pcVar3 + 4;
  }
  // Copy controller name (64 bytes at +0x444)
  puVar5 = (undefined4 *)(iVar2 + 0x444);
  pcVar3 = local_448;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *(undefined4 *)pcVar3 = *puVar5;
    puVar5 = puVar5 + 1;
    pcVar3 = pcVar3 + 4;
  }
  // Check if controller name is non-empty
  pcVar3 = local_448;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  if (pcVar3 != local_448 + 1) {
    // Check if controller data is non-empty
    pcVar3 = local_408;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    if (pcVar3 != local_408 + 1) {
      // Process controller data and name (likely XInput state)
      FUN_00566de0(local_408,local_448);
      // Clear controller slot at offset +0x484
      FUN_008a1850(DAT_0113058c * 0x504 + 0x484 + DAT_0113055c);
    }
  }
  // Set controller update flag
  FUN_00566a60(1);
  iVar2 = DAT_01129928;
  DAT_01130590 = DAT_01130590 & 0xffffffbf; // Clear bit 6
  DAT_00e5672c = 0xc; // Set some timer/state
  *(undefined4 *)(DAT_01129928 + 0x60) = 0; // Clear some field
  if ((DAT_01130590 & 1) == 0) {
    // Initialize controller if not already done
    FUN_005c0d50(iVar2 + 0x14,&LAB_00931e00,0);
    DAT_01130590 = DAT_01130590 | 1; // Set initialization flag
  }
  return;
}