// FUNC_NAME: Player::checkAndSetDonMode
char Player::checkAndSetDonMode(int thisPtr)
{
  char result;
  char isDonModeActive;
  undefined4 unused1;
  undefined4 unused2;
  undefined8 unused3;
  undefined4 unused4;
  
  isDonModeActive = FUN_00798f50(7); // Check if don mode is globally active
  result = FUN_0079e970(isDonModeActive); // Get don mode state
  if (result == '\0') {
    // Don mode not globally active, check local conditions
    char canEnterDonMode = FUN_00481640(); // Check if player can enter don mode
    if (((canEnterDonMode != '\0') && (*(char *)(thisPtr + 0x21b4) == '\0')) && // +0x21b4: donModeActive flag
       (*(int *)(thisPtr + 0x21bc) == 1)) { // +0x21bc: some state counter/flag
      *(undefined1 *)(thisPtr + 0x21b4) = 1; // Set don mode active
      return '\x01'; // Success
    }
  }
  else {
    // Don mode is globally active, log something
    unused1 = CONCAT31(unused1._1_3_,1);
    FUN_0079fb90(1,CONCAT44(3,unused1),CONCAT44(unused2,1),unused3,unused4); // Logging function
  }
  return result;
}