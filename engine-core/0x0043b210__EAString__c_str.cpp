// FUNC_NAME: EAString::c_str
// Function at 0x0043b210: Returns the C-string buffer of an EA-style string with short string optimization.
// Structure:
//   0x00: char m_shortLength; // length of inline string (0 if using external pointer)
//   0x14: char m_inlineBuffer[0x48]; // inline buffer for short strings (size 72? Actually offset 0x5c - 0x14 = 0x48)
//   0x5c: char* m_externalPtr; // pointer to external string when length > buffer size

char* EAString::c_str()
{
    char* result;

    // If the short length is zero (i.e., no inline string), use the external pointer.
    if (m_shortLength == '\0')
    {
        result = m_externalPtr; // +0x5c
    }
    else
    {
        result = m_inlineBuffer; // +0x14
    }

    return result;
}