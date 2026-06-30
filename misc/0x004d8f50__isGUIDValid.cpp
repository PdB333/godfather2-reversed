// FUNC_NAME: isGUIDValid
// Function at 0x004d8f50: Checks if a GUID string is not the invalid/sentinel GUID "{BADBADBA-BEEF-BEEF-555A-C1EA11091091}".
// Returns true if the string is NULL or does NOT match the bad GUID (i.e., it's considered "valid").
// Returns false if the string matches the bad GUID.
// Uses __fastcall convention: param_1 in ecx.
bool __fastcall isGUIDValid(char* param_1)
{
    int cmpResult;
    
    // A null pointer is treated as valid (not the bad GUID).
    if (param_1 != (char*)0x0) {
        // Case‑insensitive compare against the sentinel GUID.
        cmpResult = __stricmp(param_1, "{BADBADBA-BEEF-BEEF-555A-C1EA11091091}");
        // Return true if strings differ (i.e., not the bad GUID).
        return cmpResult != 0;
    }
    return true;
}