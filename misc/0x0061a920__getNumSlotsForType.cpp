// FUNC_NAME: getNumSlotsForType
// Address: 0x0061a920
// Role: Returns the number of slots/items for a given type (likely inventory or weapon type enumeration).
// Values 0x1E-0x23 (30-35) return 4, all others return 1.

int __fastcall getNumSlotsForType(int type)
{
    // Only certain types have 4 slots; the rest have 1.
    if ((type == 0x1E) || (type == 0x1F) || (type == 0x20) || 
        (type == 0x21) || (type == 0x22) || (type == 0x23))
    {
        return 4;
    }
    return 1;
}