// FUNC_NAME: InputManager::initKeyMappingTable
void InputManager::initKeyMappingTable(void)
{
  uint i;
  
  i = 0;
  do {
    gKeyMappingTable[i] = (char)i; // +0x00: Direct mapping of scancode to key index (0-0x4F)
    i = i + 1;
  } while (i < 0x50);
  gKeyMappingCount = 0x50; // DAT_00e53770 - number of mapped keys
  return;
}