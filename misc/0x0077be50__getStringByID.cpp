// FUNC_NAME: getStringByID
// Function at 0x0077be50: Retrieves a string pointer from a lookup table based on an index.
// The table stores pointers with stride 3 (likely for string, length, or other data).
// param_1: index into the table (e.g., an enum value for HUD elements).
// Returns: pointer to the associated string (e.g., "HEALTH_PERCENTAGE").

const char* getStringByID(int stringID)
{
    // Array of string pointers, defined elsewhere (e.g., PTR_s_HEALTH_PERCENTAGE_00e51d64)
    // Each entry occupies 3 pointer slots; the string pointer is at base + (index * 3).
    extern const char* g_stringTable[]; // Assume this is the external table
    return g_stringTable[stringID * 3];
}