// FUNC_NAME: WideString::compare
int __thiscall WideString::compare(const WideString* other) const
{
    // Class layout:
    // +0x00: ushort* data  (pointer to UTF-16 string)
    // +0x04: int length    (number of ushorts, or 0 if empty)

    // Handle empty cases
    if (this->length == 0) {
        // this is empty: return 0 if other is also empty, else 1
        return (other->length != 0) ? 1 : 0;
    }
    if (other->length == 0) {
        // this is non-empty, other is empty
        return -1;
    }

    const ushort* pSelf = this->data;
    const ushort* pOther = other->data;

    while (true) {
        // Compare first ushort (high surrogate? or low?)
        ushort selfFirst = *pSelf;
        ushort otherFirst = *pOther;

        if (selfFirst != otherFirst) {
            return (selfFirst < otherFirst) ? -1 : 1;
        }
        // If both are null terminator (end of string), strings are equal
        if (selfFirst == 0) {
            return 0;
        }

        // Compare second ushort (low surrogate or next character)
        ushort selfSecond = pSelf[1];
        ushort otherSecond = pOther[1];
        if (selfSecond != otherSecond) {
            return (selfSecond < otherSecond) ? -1 : 1;
        }
        // Advance by two ushorts (one 32-bit unit, e.g. surrogate pair)
        pSelf += 2;
        pOther += 2;
        if (selfSecond == 0) {
            return 0;
        }
    }
}