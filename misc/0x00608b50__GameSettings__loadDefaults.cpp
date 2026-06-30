// FUNC_NAME: GameSettings::loadDefaults
void __thiscall GameSettings::loadDefaults(void)
{
  // this points to a structure of size 0x38 bytes (14 dwords)
  char fullscreenFlag;
  int profileIndex;
  uint profileValue;
  uint arrayIndex;
  uint *currentEntry;
  bool isFullscreen;
  uint tempLocal;

  _memset(this, 0, 0x38);

  // Initialize from global configuration constants
  this->magicOrVersion = (uint)DAT_0120587c;
  fullscreenFlag = DAT_0120587f;
  isFullscreen = DAT_0120587f != '\0';
  this->resolutionWidth = (uint)DAT_01205880;       // +0x04
  this->displayIndex = 1;                            // +0x0C
  this->refreshrate = 0;                             // +0x10
  this->unknownField5 = 0;                           // +0x14
  this->fullscreenBits = -(uint)isFullscreen & 0x15; // +0x08  (0x15 = 21 decimal, bitfield)
  this->windowMode = 1;                              // +0x18
  this->selectedProfileValue = profileValue;          // +0x1C
  this->isFullscreen = (uint)(fullscreenFlag == '\0'); // +0x20 (inverted)
  this->unknownField10 = 0;                          // +0x28
  this->unknownField9 = 0;                           // +0x24
  this->unknownField11 = 0;                          // +0x2C

  tempLocal = 0;
  profileValue = 0;
  // Search through stored profiles for first active profile with ID 1
  if (DAT_01222520 != 0) {
    arrayIndex = 0;
    profileValue = tempLocal;
    if (*(uint *)(DAT_0122251c + 8) != 0) {
      currentEntry = *(uint **)(DAT_0122251c + 4);
      do {
        if ((*(char *)(currentEntry + 3) == '\0') && (*(int *)(currentEntry + 1) == 1)) {
          profileValue = *(uint *)(currentEntry + 9); // +0x24
          break;
        }
        arrayIndex = arrayIndex + 1;
        currentEntry = currentEntry + 0x53; // 0x14c bytes per profile entry
      } while (arrayIndex < *(uint *)(DAT_0122251c + 8));
    }
  }

  // Set video mode flags based on global settings
  if (fullscreenFlag == '\0') {
    this->screenWidth = 0;             // +0x30
    this->screenHeight = 0x80000000;   // +0x34 (sentinel)
    return;
  }

  isFullscreen = DAT_00f15a39 != '\0'; // additional flag (e.g., HDTV)
  this->screenWidth = (uint)DAT_01205760; // +0x30
  if (isFullscreen) {
    if ((profileValue & 2) == 0) {
      this->screenHeight = profileValue & 1; // +0x34
      return;
    }
    this->screenHeight = 2;
    return;
  }
  this->screenHeight = profileValue & 0x80000000;
  return;
}