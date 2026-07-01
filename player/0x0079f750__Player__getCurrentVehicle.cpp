// FUNC_NAME: Player::getCurrentVehicle
int __fastcall Player::getCurrentVehicle(int thisPtr)
{
  char cVar1;
  int iVar2;
  
  // Check if player is in a vehicle (vehicle pointer at +0x2528)
  if ((*(int *)(thisPtr + 0x2528) == 0) || (iVar2 = *(int *)(thisPtr + 0x2528) + -0x48, iVar2 == 0))
  {
    // Check if player is in a different vehicle slot (+0x1c78)
    if (*(int *)(thisPtr + 0x1c78) == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(thisPtr + 0x1c78) + -0x48;
      if (iVar2 != 0) {
        return iVar2;
      }
    }
    // Check if player is in a special vehicle state via global function
    cVar1 = FUN_007f7c50(); // likely isPlayerInVehicle() or similar
    if (cVar1 != '\0') {
      // Check another vehicle pointer at +0x24fc (possibly passenger seat)
      if (*(int *)(thisPtr + 0x24fc) != 0) {
        return *(int *)(thisPtr + 0x24fc) + -0x48;
      }
      return 0;
    }
  }
  return iVar2;
}