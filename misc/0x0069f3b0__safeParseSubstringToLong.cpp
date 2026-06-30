// FUNC_NAME: safeParseSubstringToLong
bool safeParseSubstringToLong(long* outValue, uint length, const char* buffer, uint bufferSize)
{
    // Check if the substring is not the complete token: if there is a character following the substring within buffer bounds,
    // and that character is a digit (1 through 8 only – likely a bug, should be any digit), reject.
    if ((length + 1 < bufferSize) && (buffer[length + 1] > '0') && (buffer[length + 1] < '9'))
    {
        return false;
    }

    uint i = 0;
    bool allDigits = true;

    // Validate that all characters are digits
    if (length != 0)
    {
        do
        {
            if (allDigits && _isdigit((int)buffer[i]))
            {
                allDigits = true;
            }
            else
            {
                allDigits = false;
            }
            i++;
        } while (i < length);

        if (!allDigits)
        {
            return false;
        }
    }

    // Copy the substring to a 8-byte stack buffer (max 7 digits + null) and convert to long
    char temp[8];
    _memcpy(temp, buffer, length);
    temp[length] = '\0';
    *outValue = _atol(temp);
    return allDigits; // true if all characters were digits
}