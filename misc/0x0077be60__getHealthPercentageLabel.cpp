// FUNC_NAME: getHealthPercentageLabel
// Address: 0x0077be60
// Role: Returns a pointer to a health percentage string from a static lookup table.
// The table (at 0x00e51d64) is an array of const char* pointers, indexed by (index * 3).
// This multiplier suggests each logical entry occupies 3 consecutive pointers (e.g., for different languages or tiers).
extern const char* const PTR_s_HEALTH_PERCENTAGE_00e51d64; // base pointer to first string in array

const char* __cdecl getHealthPercentageLabel(int param_1)
{
    // Return the string pointer at offset param_1 * 3 from the base
    return (&PTR_s_HEALTH_PERCENTAGE_00e51d64)[param_1 * 3];
}