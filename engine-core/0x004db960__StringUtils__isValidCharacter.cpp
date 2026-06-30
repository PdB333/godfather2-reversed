// FUNC_NAME: StringUtils::isValidCharacter
uint __fastcall StringUtils::isValidCharacter(wchar_t character)
{
  uint result;
  wchar_t *found;
  undefined8 validChars[4]; // 8 bytes each, total 32 bytes
  undefined2 extraChar; // +0x20

  // Load valid character set from global data
  validChars[0] = DAT_00e36e70;
  validChars[1] = DAT_00e36e78;
  validChars[2] = DAT_00e36e80;
  validChars[3] = DAT_00e36e88;
  extraChar = DAT_00e36e90; // +0x20

  result = (uint)(ushort)character;

  // Check if character is alphanumeric (a-z, A-Z, 0-9)
  if (((0x19 < result - 0x61) && (0x19 < result - 0x41)) && (result = result - 0x30, 9 < result)) {
    // Not alphanumeric, search in the valid character set
    found = _wcschr((wchar_t *)validChars, character);
    return (uint)(found != (wchar_t *)0x0);
  }
  // Alphanumeric characters are always valid
  return CONCAT31((int3)(result >> 8), 1);
}