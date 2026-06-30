// FUNC_NAME: setInputAxisValueWithInvert
// Address: 0x0064be30 - Sets a signed input axis value, optionally inverting the sign based on a configuration flag.
// The index is 1-based (low byte of first parameter), stored 0-based after decrement.
void setInputAxisValueWithInvert(int index, int value)
{
    char rawIndex = (char)index;                 // Extract low byte as index
    char invertFlag = FUN_0064bb50(value < 0);   // Check if value should be inverted (e.g., invert axis setting)
    if (invertFlag != '\0') {
        value = -value;                          // Invert value if flag set
    }
    FUN_0064b810(rawIndex - 1, &value);          // Store value in zero‑based slot
}