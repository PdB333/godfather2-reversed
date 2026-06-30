// FUNC_NAME: EARSObject::sanitizeStateFlags
// Address: 0x0049e1b0
// Clamps five boolean fields to valid 0/1 values; called during initialization.

class EARSObject
{
public:
    // Fields at documented offsets relative to this pointer
    int field_0x0c; // +0x0c: first boolean flag
    int field_0x14; // +0x14: second boolean flag
    int field_0x1c; // +0x1c: third boolean flag
    int field_0x24; // +0x24: fourth boolean flag
    int field_0x2c; // +0x2c: fifth boolean flag

    // Ensures each flag is either 0 or 1; otherwise resets to 0.
    void __thiscall sanitizeStateFlags(void)
    {
        if (field_0x0c != 0 && field_0x0c != 1)
            field_0x0c = 0;
        if (field_0x14 != 0 && field_0x14 != 1)
            field_0x14 = 0;
        if (field_0x1c != 0 && field_0x1c != 1)
            field_0x1c = 0;
        if (field_0x24 != 0 && field_0x24 != 1)
            field_0x24 = 0;
        if (field_0x2c != 0 && field_0x2c != 1)
            field_0x2c = 0;
    }
};