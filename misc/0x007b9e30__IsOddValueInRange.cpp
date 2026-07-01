// FUNC_NAME: IsOddValueInRange
// Function address: 0x007b9e30
// Returns 1 if param_1 is an odd number between 1 and 0x3B (59) inclusive, otherwise 0.
// This is likely a helper to check if a value belongs to a specific set of odd indices (e.g., animation slots, controller buttons, or state IDs).

int IsOddValueInRange(unsigned char value)
{
    switch (value)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
    case 0xB:
    case 0xD:
    case 0xF:
    case 0x11:
    case 0x13:
    case 0x15:
    case 0x17:
    case 0x19:
    case 0x1B:
    case 0x1D:
    case 0x1F:
    case 0x21:
    case 0x23:
    case 0x25:
    case 0x27:
    case 0x29:
    case 0x2B:
    case 0x2D:
    case 0x2F:
    case 0x31:
    case 0x33:
    case 0x35:
    case 0x37:
    case 0x39:
    case 0x3B:
        return 1;
    default:
        return 0;
    }
}