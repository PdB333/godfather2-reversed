// FUNC_NAME: Player::canEnterVehicle
undefined1 __fastcall Player::canEnterVehicle(int thisPtr)
{
  int iVar1;
  int iVar2;
  undefined1 result;
  int iVar4;
  int *vehicleSlotPtr;
  
  result = 1;
  vehicleSlotPtr = (int *)(thisPtr + 0xa4c); // +0xA4C: vehicle slot array start (4 slots)
  iVar4 = 4;
  do {
    iVar1 = *vehicleSlotPtr;
    if (iVar1 != 0) {
      iVar2 = FUN_00791300(); // likely getVehicleBrain or getVehicleState
      if (iVar2 == 0) {
        if ((*(uint *)(iVar1 + 0x5c) & 0x60000) != 0) { // +0x5C: vehicle flags, check 0x60000 (occupied/destroyed?)
          result = 0;
        }
      }
      else {
        FUN_004088c0(iVar2 + 0x3c); // +0x3C: some vehicle state field, maybe setOccupied or similar
      }
    }
    vehicleSlotPtr = vehicleSlotPtr + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return result;
}