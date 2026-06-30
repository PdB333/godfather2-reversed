// FUNC_NAME: getGlobalExtendedFloat
// Function address: 0x006dc860
// Returns the 80-bit extended precision float stored at global address 0x00d5ef88.
long double getGlobalExtendedFloat(void) {
    // DAT_00d5ef88
    return g_extendedFloatValue;
}