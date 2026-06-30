// FUNC_NAME: UUIDParser::parseUUID
undefined4 * __thiscall FUN_004d8ce0(undefined4 *this, char *uuidString)

{
  int comparisonResult;
  
  if (uuidString == (char *)0x0) {
    comparisonResult = 1;
  }
  else {
    comparisonResult = __stricmp(uuidString,"{BADBADBA-BEEF-BEEF-555A-C1EA11091091}");
  }
  if (comparisonResult != 0) {
    // Not the special BAD UUID, parse normally
    FUN_004d9500(uuidString);
    return this;
  }
  // Special BAD UUID: store raw bytes directly
  this[0] = 0xbadbadba;  // +0x00: first DWORD
  this[1] = 0xbeefbeef;  // +0x04: second DWORD
  this[2] = 0xeac15a55;  // +0x08: third DWORD
  this[3] = 0x91100911;  // +0x0C: fourth DWORD
  return this;
}