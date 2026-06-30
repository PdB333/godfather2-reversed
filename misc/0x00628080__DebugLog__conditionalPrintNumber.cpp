// FUNC_NAME: DebugLog::conditionalPrintNumber
// Address: 0x00628080
// This function conditionally prints the string "number" based on two debug flags.
// It is called from many places (at least 18 callers), likely a macro-like debug helper.
// The two checks: FUN_006259b0 (returns float) must be 0, and FUN_006257d0 (returns int) must be 0.
// If both conditions are met, it calls FUN_00627ac0 to output "number".
// This could be a debug system for tracking events or object counts (e.g., "number" = number of something).

void DebugLog::conditionalPrintNumber()
{
    // Check first debug flag (float comparison, likely a tolerance or state flag)
    float debugFlagFloat = getDebugFloatFlag(); // FUN_006259b0 - returns float
    if (debugFlagFloat == 0.0f)
    {
        // Check second debug flag (integer condition)
        int debugFlagInt = getDebugIntFlag(); // FUN_006257d0 - returns int
        if (debugFlagInt == 0)
        {
            // Both flags are "off" or "false", so print the debug string "number"
            printDebugString("number"); // FUN_00627ac0 - prints null-terminated string to debug output
        }
    }
    return;
}