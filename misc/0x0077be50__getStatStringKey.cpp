// FUNC_NAME: getStatStringKey
// Address: 0x0077be50
// Role: Returns a pointer to a stat string key from a lookup table, indexed by stat ID.
// The table at 0x00e51d64 contains pointers to string keys (like "HEALTH_PERCENTAGE", etc.)
// Index is param_1 * 3 (perhaps each stat has 3 entries? or byte alignment?)

__cdecl const char* getStatStringKey(int statId)
{
    // Table of string keys (e.g. "HEALTH_PERCENTAGE", "ARMOR_PERCENTAGE", etc.)
    // Note: The original code used undefined* but this likely returns char* or const char*
    return (&s_statStringKeysTable)[statId * 3]; // +0x00e51d64: start of table
}