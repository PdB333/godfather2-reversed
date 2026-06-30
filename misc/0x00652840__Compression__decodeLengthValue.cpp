// FUNC_NAME: Compression::decodeLengthValue
// Function at 0x00652840: Decodes a length value from a compressed bitstream using difference encoding.
// Parameters: code (EAX) - combined encoded data, base (EDI) - base offset/previous value.
// Returns: decoded integer (length or position).
int __fastcall decodeLengthValue(int code, int base)
{
    int diff = code - base + 1;   // difference + 1
    float fDiff = (float)diff;    // convert to float for exponent extraction
    if (diff < 0)
    {
        fDiff += 4294967296.0f;   // DAT_00e44578 = 2^32, adjust for negative (unsigned wrap)
    }

    // Extract exponent bits from float (bits 23-30) and combine with conditional.
    // (code - base) & diff checks if the original difference and diff share any bits.
    // The result is an exponent-like value used to determine how many bits to read next.
    int expByte = (((code - base) & diff) != 0) - 0x7F + ((uint32_t)fDiff >> 0x17);
    // expByte is now in range roughly 0..255

    int additionalValue = 0;
    readBits(expByte & 0xFF, &additionalValue); // FUN_0064b9e0: reads expByte bits from stream into additionalValue

    if ((expByte & 0xFF) == 0x20)
    {
        return additionalValue + base;
    }
    else
    {
        return ((1 << (expByte & 0x1F)) - 1) & additionalValue + base;
    }
}