// FUNC_NAME: DecodePropertyMask
// Function at 0x00541430: Decodes a packed property tag into either a bit mask, a table lookup value, or a sentinel.
// The top 2 bits determine the encoding type:
//   00 -> returns a mask from bit position stored in bits 5-9 (1 << (tag>>5 & 0x1f))
//   01 -> returns value from table starting at address 8, indexed by tag
//   10 -> returns sentinel 0x80000000
//   11 -> returns value from table starting at address 0x54, indexed by tag
// The table bases (8 and 0x54) are likely resolved relative to a hidden this pointer or a global; here shown as direct offsets.

int __fastcall DecodePropertyMask(uint tag)
{
    uint tagType = tag & 0xC0000000;

    if (tagType == 0)
    {
        // Bit mask: extract shift value from bits 5-9 (0..31)
        return 1 << ((tag >> 5) & 0x1F);
    }
    else if (tagType == 0x40000000)
    {
        // Table access at offset 0x8 (e.g., inside a global structure)
        return *(int *)(tag * 4 + 8);
    }
    else if (tagType == 0xC0000000)
    {
        // Table access at offset 0x54
        return *(int *)(tag * 4 + 0x54);
    }
    else // tagType == 0x80000000
    {
        // Sentinel value (negative maximum int)
        return 0x80000000;
    }
}