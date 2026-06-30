// FUNC_NAME: EARSVersion::checkVersion
void __thiscall EARSVersion::checkVersion(const char *versionString)
{
  bool versionValid;
  char stringFormat; // local_64 - indicates whether string is dotted decimal or single token
  int tokenVal1; // local_58
  int tokenVal2; // local_54
  int tokenArray[18]; // local_50 - parsed version tokens (max 18)
  int *tokenPtr; // local_8 - pointer into tokenArray or to a single integer

  // Step 1: Verify the version string against a known hash (CRC32?)
  compareVersionHash(versionString, 0x66f692b3);

  // Step 2: Reset internal parsing state
  resetVersionParsing();

  // Step 3: Determine format of version string and run validity check
  if (stringFormat == '\0') {
    // Single token format: tokenPtr points to a single integer (uninitialized here)
    versionValid = (*tokenPtr == 0);
  } else {
    // Dotted decimal format (e.g., "1.2.3"): compare two parsed token values
    versionValid = (tokenVal1 == tokenVal2);
  }

  // Step 4: If validation failed, update the result flag based on the third token
  if (!versionValid) {
    if (stringFormat != '\0') {
      // For dotted format, ensure tokenPtr points to the token array
      tokenPtr = tokenArray;
    }
    // Set member bool at +0x55 to indicate whether the third token is non-zero
    // (likely indicating a sub-version or build number mismatch)
    *(bool *)(this + 0x55) = (tokenPtr[2] != 0);
  }

  return;
}