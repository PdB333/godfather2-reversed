// FUNC_NAME: getThresholdCategory
int __thiscall getThresholdCategory(int this, uint value)
{
    // Threshold sizes stored as bytes at offsets +0x80, +0x81, +0x82 (cumulative)
    uint tier0Size = (uint)*(byte *)(this + 0x80);  // +0x80: size of first range
    uint tier1Size = (uint)*(byte *)(this + 0x81);  // +0x81: size of second range
    uint tier2Size = (uint)*(byte *)(this + 0x82);  // +0x82: size of third range

    uint tier1End = tier0Size + tier1Size;
    uint tier2End = tier1End + tier2Size;

    if (value < tier0Size)
        return 0;                                    // first category
    if (value < tier1End)
        return 1;                                    // second category
    if (value < tier2End)
        return 2;                                    // third category
    return -1;                                       // outside all ranges
}