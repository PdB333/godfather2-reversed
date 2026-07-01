// FUNC_NAME: GodfatherGameManager::updatePlayerVehicleState
void __fastcall GodfatherGameManager::updatePlayerVehicleState(int this)
{
  char cVar1;
  undefined1 local_19;
  undefined1 local_18 [12];
  undefined1 local_c [12];
  
  // Check if bit 0 of flags at +0x428 is clear (not paused?) and bit 1 of +0x170 is set (player in vehicle?)
  if (((*(byte *)(this + 0x428) & 1) == 0) && ((*(uint *)(this + 0x170) >> 1 & 1) != 0)) {
    // Check if current game state is either 0 (menu?) or 0x48 (driving?)
    if ((*(int *)(DAT_011298e4 + 100) == 0) || (*(int *)(DAT_011298e4 + 100) == 0x48)) {
      // Copy vehicle speed/velocity from player to global game state
      *(undefined4 *)(DAT_011298e4 + 0xa0) = *(undefined4 *)(this + 0x178);
      cVar1 = FUN_008f95e0(local_c, local_18, &local_19, 4);
      if (cVar1 != '\0') {
        FUN_00909bf0(local_c, local_18);
      }
    }
  }
  return;
}