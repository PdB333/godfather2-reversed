// FUNC_NAME: Identifier::operator==
// Function at 0x00487150: Compares two 24-byte identifiers for equality.
// If the other identifier's 'size' field (at +0x18) is zero, only the first
// dword is compared. Otherwise all 6 dwords are checked.
bool __fastcall Identifier::operator==(const Identifier* this, const Identifier* other) const
{
    // If same object, implicitly equal
    if (other == this)
        return true;

    // Check the 'size' flag in the other object (+0x18)
    // If zero, only compare the first dword (e.g., a hash or id)
    if (*(int*)((byte*)other + 0x18) == 0)
        return *(int*)other == *(int*)this;

    // Otherwise compare all 24 bytes (6 dwords) directly
    int remaining = 0x18; // 24 bytes to compare
    const byte* pThis = (const byte*)this;
    const byte* pOther = (const byte*)other;

    // Compare dword by dword while at least 4 bytes remain
    do {
        if (*(int*)pOther != *(int*)pThis)
            goto byteCompare; // fall through to byte-by-byte
        remaining -= 4;
        pThis += 4;
        pOther += 4;
    } while (remaining > 3);

    // If all dwords matched, the objects are equal
    if (remaining == 0)
        return true;

    // Byte-by-byte comparison for partial dword (should never reach here for 24-byte struct)
byteCompare:
    int diff = *pOther - *pThis;
    if (diff != 0)
    {
        // If diff < 0, other is smaller => not equal
        if (diff < 1)
            return false;
        // Otherwise diff > 0 => not equal
        return false;
    }

    // If first byte equal, check remaining bytes
    if (remaining == 1)
        return true;
    diff = pOther[1] - pThis[1];
    if (diff != 0)
    {
        if (diff < 1) return false;
        return false;
    }
    if (remaining == 2)
        return true;
    diff = pOther[2] - pThis[2];
    if (diff != 0)
    {
        if (diff < 1) return false;
        return false;
    }
    if (remaining == 3)
        return true;
    diff = pOther[3] - pThis[3];
    if (diff != 0)
    {
        if (diff < 1) return false;
        return false;
    }
    return true;
}