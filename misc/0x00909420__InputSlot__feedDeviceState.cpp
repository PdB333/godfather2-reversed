// FUNC_NAME: InputSlot::feedDeviceState
undefined4 __thiscall InputSlot::feedDeviceState(uint thisPtr, int deviceState)
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 uStack_4;

  // State check: state at +0x64 must be 0 or 0x48 (active)
  if ((*(int *)(thisPtr + 100) != 0) && (*(int *)(thisPtr + 100) != 0x48)) {
    return 0;
  }
  // Process only if deviceState is valid and (device type is 2 (gamepad) or bit1+bit0 conditions)
  if ((deviceState != 0) &&
     (((uStack_4 = thisPtr, iVar2 = FUN_008c7510(*(undefined4 *)(thisPtr + 0xa0)), iVar2 == 2 ||
       ((*(uint *)(thisPtr + 0xb4) >> 1 & 1) != 0)) && ((*(byte *)(thisPtr + 0xb4) & 1) == 0)))) {
    // Clear previous input state from device side
    FUN_00909040(deviceState);
    // Copy raw stick/trigger values from device state (+0xB4, +0xBC) to this slot (+0xA4, +0xAC)
    *(undefined8 *)(thisPtr + 0xa4) = *(undefined8 *)(deviceState + 0xb4);
    *(undefined4 *)(thisPtr + 0xac) = *(undefined4 *)(deviceState + 0xbc);
    // Update timestamp: slot's own prev + global offset
    *(int *)(thisPtr + 0xb0) = *(int *)(thisPtr + 0xcc) + DAT_01205224;
    // Iterate over 6 input axes/buttons (each 0x10 bytes) starting at deviceState+0x54
    iVar2 = deviceState + 0x54;
    if (iVar2 != 0) {
      uVar5 = 0;
      do {
        // Check global input processing flags (e.g., menu open, debug mode)
        cVar1 = FUN_00445250();
        if ((cVar1 != '\0') && (cVar1 = FUN_004209a0(), cVar1 == '\0')) {
          // Compute unique action ID from this slot's address (lower 24 bits + high byte of address)
          uStack_4 = uStack_4 & 0xffffff;
          iVar3 = FUN_00448100(iVar2,(int)&uStack_4 + 3);
          if (iVar3 != 0) {
            // Prepare input handling for this slot
            FUN_00810c10(thisPtr);
            // Determine feedback slot: if device is gamepad (type 2) or button mask has this axis,
            // use an offset of +100; else use +0xd0 (first 3) or +0xe0 (last 3) within thisPtr
            iVar4 = FUN_008c7510(*(undefined4 *)(thisPtr + 0xa0));
            if ((iVar4 == 2) || ((*(uint *)(deviceState + 0xc0) & 1 << ((byte)uVar5 & 0x1f)) != 0)) {
              iVar3 = iVar3 + 100;
            }
            else {
              iVar3 = thisPtr + 0xd0;
              if (2 < uVar5) {
                iVar3 = thisPtr + 0xe0;
              }
            }
            // Set feedback state (e.g., rumble motor, LED)
            FUN_00810c90(iVar3,1);
          }
        }
        uVar5 = uVar5 + 1;
        iVar2 = iVar2 + 0x10;
      } while (uVar5 < 6);
    }
    // Finalize input processing for this slot
    FUN_00909150();
    return 1;
  }
  return 0;
}