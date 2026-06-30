// FUNC_NAME: unknown::getFlagColor
// Function at 0x005d07d0: returns a color based on two flag bits (bit 10 and 11) at offset 0x18.
// Colors: 0=dark blue (0xff040a52), 0x400=white (0xffffffff), 0x800=orange (0xff663300), 0xc00=black (0xff000000).
// Probably used for UI or status indication (e.g., threat level, team color).

uint32 getFlagColor() const
{
    uint32 flags = *(uint32*)(this + 0x18);        // +0x18: state/flags field
    uint32 masked = flags & 0xC00;                  // Extract bits 10 and 11

    if (masked < 0x801)
    {
        if (masked == 0x800)
            return 0xFF663300;                      // Orange
        if ((masked != 0) && (masked == 0x400))
            return 0xFFFFFFFF;                      // White
    }
    else if (masked == 0xC00)
    {
        return 0xFF000000;                          // Black
    }
    return 0xFF040A52;                              // Dark blue (default)
}