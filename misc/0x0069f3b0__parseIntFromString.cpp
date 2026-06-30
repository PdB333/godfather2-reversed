// FUNC_NAME: parseIntFromString
bool parseIntFromString(int32_t* outValue, uint32_t startOffset, const void* data, uint32_t dataLen)
{
    // Check if the character after the substring is a digit; if so, it's part of a larger number -> invalid
    if ((startOffset + 1 < dataLen) && 
        (*(char*)((uintptr_t)data + startOffset + 1) > '0') && 
        (*(char*)((uintptr_t)data + startOffset + 1) < '9'))
    {
        return false;
    }

    uint32_t i = 0;
    bool allDigits = true;

    if (startOffset != 0)
    {
        do
        {
            if (allDigits && isdigit(*(char*)((uintptr_t)data + i)))
            {
                allDigits = true;
            }
            else
            {
                allDigits = false;
            }
            i++;
        } while (i < startOffset);

        if (!allDigits)
        {
            return false;
        }
    }

    // Copy the substring into a local buffer and parse as integer
    char buffer[8]; // Assumes startOffset < 8
    memcpy(buffer, data, startOffset);
    buffer[startOffset] = '\0';
    *outValue = atol(buffer);
    return allDigits;
}