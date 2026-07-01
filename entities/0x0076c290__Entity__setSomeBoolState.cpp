// FUNC_NAME: Entity::setSomeBoolState
void __thiscall Entity::setSomeBoolState(int this, unsigned int param_2)
{
    // +0x8c: flags field, bit 1 (value 2) indicates some boolean state
    unsigned int flags = *(unsigned int*)(this + 0x8c);
    bool currentState = (flags >> 1) & 1;  // Extract bit 1

    if ( (param_2 & 0xFF) != currentState )
    {
        // Call to handle the state change externally
        FUN_0072cb10(param_2);  // Possibly a callback or event

        // Update the flag bit based on new state
        if ( (param_2 & 0xFF) == 0 )
        {
            // Clear bit 1
            flags &= ~2U;
        }
        else
        {
            // Set bit 1
            flags |= 2U;
        }
        *(unsigned int*)(this + 0x8c) = flags;

        // Update timestamps (or other values) at +0x78 and +0x74
        *(unsigned int*)(this + 0x78) = FUN_00716100();  // e.g., current time
        *(unsigned int*)(this + 0x74) = FUN_00715e30();  // e.g., duration or start time
    }
}