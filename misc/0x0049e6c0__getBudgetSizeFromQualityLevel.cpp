// FUNC_NAME: getBudgetSizeFromQualityLevel
// Address: 0x0049e6c0
// This function maps a quality level enum (0-4) to a budget size.
// Used by rendering/audio subsystem to determine allocation sizes.
// Cases 1-3 return 0x10 (16 bytes), case 4 returns 0x40 (64 bytes), default 0.
int getBudgetSizeFromQualityLevel(int qualityLevel)
{
    switch (qualityLevel)
    {
    case 1: // Low
    case 2: // Medium
    case 3: // High
        return 0x10;
    case 4: // Ultra
        return 0x40;
    default:
        return 0;
    }
}