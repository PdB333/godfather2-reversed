// FUNC_NAME: Player::isInVehicleOrSomething
uint __fastcall Player::isInVehicleOrSomething(int this)
{
  int vehiclePtr;
  
  vehiclePtr = *(int *)(this + 0x1ed8); // +0x1ed8: currentVehicle pointer
  if (vehiclePtr != 0) {
    // Check if vehicle is not a specific type (3 = maybe a specific vehicle class)
    // The CONCAT31 extracts the high byte of (vehiclePtr - 0x48) and combines with (*(vehiclePtr+8) != 3)
    // This is likely checking if the vehicle's type field at offset +8 is not equal to 3
    return CONCAT31((int3)((uint)(vehiclePtr + -0x48) >> 8),*(int *)(vehiclePtr + 8) != 3);
  }
  // No vehicle - check global state at 0x50 (likely a global player state flag)
  return (uint)(_DAT_00000050 != 3);
}