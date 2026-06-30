// FUNC_NAME: DifficultyConfig::init
void __thiscall DifficultyConfig::init(void *thisPtr)
{
  int *thisField;
  uint missionFlags;
  uint *missionArrayBase;
  bool flag1;
  uint local_4;
  
  // Zero-init the 0x38-byte struct
  _memset(thisPtr, 0, 0x38);
  
  thisField = (int *)thisPtr;
  thisField[0] = g_configValueA;           // +0x00
  flag1 = (g_configFlagChar != '\0');
  thisField[1] = g_configValueB;           // +0x04
  thisField[3] = 1;                         // +0x0C
  thisField[4] = 0;                         // +0x10
  thisField[5] = 0;                         // +0x14
  thisField[2] = -(uint)flag1 & 0x15;       // +0x08: 0x15 if flag1 true, else 0
  thisField[6] = 1;                         // +0x18
  thisField[7] = g_configValueC;           // +0x1C
  thisField[10] = 0;                        // +0x28
  thisField[9] = 0;                         // +0x24
  thisField[0xB] = 0;                       // +0x2C
  thisField[8] = (uint)(g_configFlagChar == '\0'); // +0x20: 1 if flag1 false
  
  local_4 = 0;
  missionFlags = 0;
  if (g_missionCount != 0) {
    uint i = 0;
    missionFlags = local_4;
    if (g_missionArraySize != 0) {
      missionArrayBase = (uint *)(g_missionArrayPtr + 4);
      do {
        // Each mission struct is 0x14C bytes
        // Check: char at +0x0C == 0 (unused) and int at +0x04 == 1 (active?)
        if ((*(char *)(missionArrayBase + 0x0C) == '\0') && (*(int *)(missionArrayBase + 0x04) == 1)) {
          missionFlags = *(uint *)(missionArrayBase + 0x24); // Flags from this mission
          break;
        }
        i++;
        missionArrayBase = (uint *)((char *)missionArrayBase + 0x14C);
      } while (i < *g_missionArraySize);
    }
  }
  
  if (g_configFlagChar == '\0') {
    thisField[0xC] = 0;                     // +0x30
    thisField[0xD] = 0x80000000;           // +0x34
    return;
  }
  
  bool flag2 = (g_secondFlag != '\0');
  thisField[0xC] = g_configValueD;         // +0x30
  if (flag2) {
    if ((missionFlags & 2) == 0) {
      thisField[0xD] = missionFlags & 1;    // +0x34
    } else {
      thisField[0xD] = 2;                   // +0x34
    }
  } else {
    thisField[0xD] = missionFlags & 0x80000000; // +0x34
  }
}