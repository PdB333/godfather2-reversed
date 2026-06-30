// FUNC_NAME: ObjectID::fromString
unsigned char __thiscall ObjectID::fromString(int *thisID, char *str)
{
  int *pParsed;
  int tmp0, tmp1, tmp2, tmp3;
  int savedLocalC;
  unsigned char result;
  char localBuffer[36];

  if ((str != (char *)0x0) && (*str != '\0')) {
    savedLocalC = 0;
    // Parse the string into a temporary buffer
    FUN_004da550(str);
    pParsed = (int *)FUN_004da7e0(localBuffer);
    // Copy the parsed 16-byte value into the output struct
    *thisID = *pParsed;
    thisID[1] = pParsed[1];
    thisID[2] = pParsed[2];
    thisID[3] = pParsed[3];
    // Check if the parsed value matches the empty/magic ID
    if ((*thisID == 0xBBADBABA) && (thisID[1] == 0xBEEFBEEF) && 
        (thisID[2] == 0xEAC15A55) && (thisID[3] == 0x91100911)) {
      result = 0; // Empty/magic ID
    } else {
      result = 1; // Non-empty ID
    }
    if (savedLocalC != 0) {
      FUN_004d8be0();
      FUN_009c8eb0(savedLocalC);
    }
    return result;
  }
  // If input is null or empty, initialize to the magic empty ID
  *thisID = 0xBBADBABA;
  thisID[1] = 0xBEEFBEEF;
  thisID[2] = 0xEAC15A55;
  thisID[3] = 0x91100911;
  return 0; // Indicates empty ID
}