// FUNC_NAME: Player::canStartMission
undefined4 __fastcall Player::canStartMission(int thisPtr)
{
  int iVar1;
  
  // Check if player is in combat (bit 10 of field at offset 0x8e0 from +0x58)
  // OR if the vehicle/vehicleState at +0x30c0 is non-zero and not 0x48 (maybe not a specific vehicle type)
  if ((((*(uint *)(*(int *)(thisPtr + 0x58) + 0x8e0) >> 10 & 1) != 0) ||
      ((iVar1 = *(int *)(*(int *)(thisPtr + 0x58) + 0x30c0), iVar1 != 0 && (iVar1 != 0x48)))) &&
     // Check if player is in a specific state (bit 4 of field at +0x4 from +0x74)
     (((*(byte *)(*(int *)(thisPtr + 0x74) + 4) & 0x10) != 0 &&
      // Check if some global state is not paused (bit 2) and that certain player flags are zero
      // (bit 5 of +0x24a4 and bit 0 of +0x249f)
      ((((iVar1 = FUN_007ab160(), (*(byte *)(iVar1 + 4) & 4) != 0 &&
         ((*(uint *)(*(int *)(thisPtr + 0x58) + 0x24a4) >> 5 & 1) == 0)) &&
        ((*(byte *)(*(int *)(thisPtr + 0x58) + 0x249f) & 1) == 0)) &&
       // Check global pointer for something (DAT_0112a838), if non-zero check its +0x5c sub-field
       ((DAT_0112a838 == 0 || (*(int *)(DAT_0112a838 + 0x5c) == 0)))))))) {
    return 1;
  }
  return 0;
}