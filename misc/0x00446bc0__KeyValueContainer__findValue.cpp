// FUNC_NAME: KeyValueContainer::findValue
// Address: 0x00446bc0
// Searches an inline key-value pair array (starting at +0xD0, count at +0x2D0) for a given key.
// Returns the associated value, or 0 if not found.
// __thiscall: this in EAX, key in EDI

int KeyValueContainer::findValue(int key)
{
    int result = 0;                  // default return value (0 if not found)
    uint index = 0;                  // loop index

    // +0x2D0: uint m_pairCount (number of valid pairs)
    if (*(uint *)(this + 0x2d0) != 0)
    {
        // +0xD0: start of inline pair array (each pair is 8 bytes: key + value)
        int *pairPtr = (int *)(this + 0xd0);

        // Walk through pairs until key matches or count exceeded
        while (*pairPtr != key)
        {
            index++;
            pairPtr += 2;            // advance to next pair (2 ints)
            if (*(uint *)(this + 0x2d0) <= index)
            {
                return result;       // not found, return 0
            }
        }
        // key found: value is the second int of the current pair
        result = pairPtr[1];
    }
    return result;
}