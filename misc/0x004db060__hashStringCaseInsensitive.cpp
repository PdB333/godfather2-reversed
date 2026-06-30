// FUNC_NAME: hashStringCaseInsensitive
int hashStringCaseInsensitive(const char* str, const char* end)
{
    int hash = 0;
    if (str != nullptr)
    {
        char ch = *str;
        while (ch != '\0' && (++str, end == nullptr || str <= end))
        {
            unsigned int c = (unsigned char)ch;
            // Convert uppercase letters (A-Z) to lowercase (a-z)
            if (c - 0x41 < 0x1a) // 'A' to 'Z' range
            {
                c += 0x20; // Convert to lowercase
            }
            hash = hash * 0x1003f + c; // sdbm-style hash multiplier
            ch = *str;
        }
    }
    return hash;
}