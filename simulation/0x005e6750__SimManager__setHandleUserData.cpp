// FUNC_NAME: SimManager::setHandleUserData
unsigned char SimManager::setHandleUserData(unsigned int handleId, int userData)
{
  // global singleton pointer to SimManager (DAT_012234bc)
  extern void* gSimManager;

  // Extract low 16 bits as slot index
  unsigned int slot = handleId & 0xffff;
  unsigned char result = 0;

  // Validate slot range (0-511) and retrieve handle entry
  if ((slot < 0x200) && 
      (int* handleEntry = (int*)((uint)(gSimManager) + slot * 0x30 + 0x10); handleEntry != 0) &&
      // Ensure the full handle matches the stored ID at +0x2c
      (*(unsigned int*)(handleEntry + 0x2c / 4) == handleId) &&
      // Check secondary data array pointer at gSimManager+0x603c
      (*(int*) ( (char*)gSimManager + 0x603c ) != 0) )
  {
    int* userDataTable = (int*)(*(int*) ((char*)gSimManager + 0x603c) + slot * 0x74);
    if (userDataTable != 0 && *userDataTable != 0) // first DWORD is a validity marker
    {
      // Store user data at offset 0x64 in this table
      userDataTable[0x19] = userData; // offset 0x64 = 0x19 * 4

      // If secondary pointer exists (at offset 8), also store user data there
      int* secondaryPtr = (int*)userDataTable[2]; // offset 8
      if (secondaryPtr != 0)
      {
        // Set bit 1 at offset 0x4a (0x4a = 0x4a bytes, but as ushort pointer)
        *(unsigned short*)((char*)secondaryPtr + 0x4a) |= 2;
        // Store user data at offset 0x54
        *(int*)((char*)secondaryPtr + 0x54) = userData;
      }
      result = 1;
    }
  }
  return result;
}