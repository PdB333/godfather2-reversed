// FUNC_NAME: Entity::getElapsedTimeAndFlag
// Address: 0x0054f220
// Role: Returns a packed value: top 24 bits = (globalTime - timer) >> 8, low 8 bits = threshold <= (globalTime - timer) ? 1 : 0.
// If timer pointer (offset +0xA4) is null, returns a base value (from an implicit register in original assembly).

uint __thiscall Entity::getElapsedTimeAndFlag(uint threshold)
{
    // NOTE: In the original assembly, EAX held a base value upon entry; this is approximated here as baseVal.
    // The exact source of baseVal is unknown; it might originate from a preceding function call.
    uint baseVal = 0; // placeholder, original code used in_EAX & 0xFFFFFF00

    // Check if timer pointer at +0xA4 is valid
    if (*(uint**)(this + 0xA4) != 0)
    {
        // Subtract object's stored timestamp from the global timer (DAT_01205224)
        uint elapsed = DAT_01205224 - **(uint**)(this + 0xA4);

        // Pack: high 24 bits = elapsed >> 8, low 8 bits = (threshold <= elapsed)
        return ((elapsed >> 8) << 8) | (threshold <= elapsed ? 1 : 0);
    }

    // If no timer, return the base value (masked to keep top 24 bits)
    return baseVal;
}