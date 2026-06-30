// FUNC_NAME: isValidGUID
// Function address: 0x004d8f50
// Role: Checks if a GUID string is valid (not null and not the special "bad" GUID)
// Returns true if valid, false if invalid (matches the bad GUID)
bool __fastcall isValidGUID(const char* guidString)
{
    if (guidString != nullptr)
    {
        // Compare case-insensitively against the known bad GUID
        int cmpResult = __stricmp(guidString, "{BADBADBA-BEEF-BEEF-555A-C1EA11091091}");
        return cmpResult != 0; // true if not equal -> valid
    }
    return true; // null pointer considered valid (or safe)
}