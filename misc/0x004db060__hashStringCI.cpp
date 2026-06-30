// FUNC_NAME: hashStringCI

int hashStringCI(const char* str, const char* endPtr)
{
    int hash = 0;

    if (str != nullptr)
    {
        char ch = *str;
        while (ch != '\0' && (++str, endPtr == nullptr || str <= endPtr))
        {
            // Convert uppercase ASCII letters to lowercase
            unsigned int lower = (unsigned int)ch;
            if (lower - 0x41 < 0x1a) // 'A' to 'Z'
            {
                lower += 0x20; // to 'a' to 'z'
            }

            hash = hash * 0x1003f + lower; // hash multiplier 65599
            ch = *str; // read next character
        }
    }

    return hash;
}