// FUNC_NAME: 0x004d48c0: EAString::findLastChar
// Role: Reverse search for a character in a string, starting from a given position or the end.

uint32_t __thiscall EAString::findLastChar(char c, uint32_t startPos) const
{
    // +0x00: char* mData (pointer to character buffer)
    // +0x04: uint32_t mLength (length of string, excluding null terminator)
    uint32_t length = this->mLength;
    uint32_t result = 0xFFFFFFFF; // sentinel for "not found"

    if (length != 0)
    {
        // Default startPos: search from the last character
        if (startPos == 0xFFFFFFFF)
        {
            startPos = length - 1;
        }

        // Validate bounds
        if (startPos < length && (int32_t)startPos >= 0)
        {
            result = startPos;
            // Scan backwards
            while (this->mData[result] != c)
            {
                if (result == 0)
                {
                    return 0xFFFFFFFF; // not found
                }
                result--;
            }
        }
    }

    return result;
}