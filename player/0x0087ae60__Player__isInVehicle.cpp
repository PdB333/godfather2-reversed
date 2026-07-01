// FUNC_NAME: Player::isInVehicle
bool __fastcall Player::isInVehicle(Player* thisPtr)
{
  int iVar1;
  
  if (thisPtr != 0) {
    iVar1 = FUN_0043b870(DAT_0113108c); // likely getPlayerVehicle or getCurrentVehicle
    if (iVar1 != 0) {
      if (*(int *)(iVar1 + 0x48) != 0) { // +0x48: vehicleType or vehicleState
        return *(int *)(iVar1 + 0x48) != 0x48; // 0x48 = VEHICLE_STATE_NONE or invalid
      }
      return false;
    }
  }
  return false;
}