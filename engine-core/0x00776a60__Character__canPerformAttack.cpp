// FUNC_NAME: Character::canPerformAttack
byte __fastcall Character::canPerformAttack(void *this)
{
  char cTemp;
  int iState;
  int iVehiclePtr;
  byte bReturn;

  // Extract bit 6 of flags at offset 0xAC: if clear, initial result is 1
  bReturn = ~((*(uint *)((int)this + 0xAC) >> 6) & 1) & 1;
  iState = *(int *)((int)this + 0x5C);               // +0x5C: state/mode

  // If bit 10 of flags is set, we potentially override
  if ((*(uint *)((int)this + 0xAC) >> 10 & 1) != 0) {
    bReturn = 0;
    iVehiclePtr = *(int *)((int)this + 0x70);          // +0x70: vehicle pointer

    // Only re-evaluate if vehicle pointer is non-zero and not a sentinel (0x48)
    if ((iVehiclePtr != 0) && (iVehiclePtr != 0x48)) {
      int iParent = iVehiclePtr - 0x48;                // compute base of vehicle object (offset 0x48 in some struct)
      if ((*(int *)(iParent + 0xA9C) != 0) &&          // +0xA9C: some condition flag inside vehicle
          (cTemp = FUN_0085e090(10), cTemp != '\0')) { // Godfather mode check (arg=10)
        bReturn = 1;
      }
    }

    // If still not allowed, attempt fallback checks
    if (bReturn == 0) {
      if (iState != 0) {
        FUN_0043b870(DAT_0113105C);                    // Log or debug function
      }
      int iGlobalState = FUN_009B2910();               // Global gameplay state
      if ((iGlobalState != 0) && (iGlobalState = FUN_007FF880(), iGlobalState != 0)) {
        return 0;                                      // Cutscene/blocked condition
      }
      return 1;                                        // Allowed by default
    }
  }
  return bReturn;
}