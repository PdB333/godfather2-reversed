// FUNC_NAME: ValidatePackedFloatId

// Validation function for a packed ID stored as float.
// Checks range, then extracts type field, and validates instance multiplication.
// Called from FUN_0061c8f0 (likely a manager or factory method).
void ValidatePackedFloatId(float value)
{
    // Global thresholds for valid packed ID values
    extern const float g_minPackedId;  // DAT_00e445bc
    extern const float g_maxPackedId;  // DAT_00e445ac
    
    if ((value < g_minPackedId) || (g_maxPackedId <= value))
        return;
    
    // Mask to extract type field from the packed value
    extern const uint g_typeMask;      // DAT_00e44680
    value = (float)((uint)value & g_typeMask);
    
    // Expected value for a valid type field
    extern const float g_validType;    // DAT_00e2b05c
    if (value != g_validType)
        DebugBreak(); // FUN_00b99fcb - assertion failure
    
    // Multiplier to check instance field (e.g., alignment or index)
    extern const float g_instanceMultiplier; // DAT_00e44728
    if (value * g_instanceMultiplier != g_validType)
    {
        DebugBreak();
        return;
    }
}