// FUNC_NAME: MathUtils::initLookupTable
void MathUtils::initLookupTable(void)
{
  uint i;
  
  i = 0;
  do {
    char c = (char)i;
    // Check if character is lowercase letter (0xbf + c < 0x1a means c in 'A'..'Z')
    if ((byte)(c + 0xbfU) < 0x1a) {
      c = c + ' '; // Convert to lowercase
    }
    // Store square of character value in lookup table at 0x01203640
    lookupTable[i] = c * c;
    i = i + 1;
  } while (i < 0x100);
  
  // Clear flag at 0x00f0ccb7
  tableInitialized = 0;
  return;
}