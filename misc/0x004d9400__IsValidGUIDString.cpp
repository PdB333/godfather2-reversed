// FUNC_NAME: IsValidGUIDString
// Function at 0x004d9400: Validates a string as a GUID in the format {XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}
// Returns true if the string matches the pattern and all X positions are valid hex digits.
bool IsValidGUIDString(const char* str)
{
    if (!str || str[0] != '{')
        return false;

    // Expected length: 38 characters (including braces and hyphens)
    size_t len = 0;
    while (str[len] != '\0')
        len++;
    if (len != 38)
        return false;

    // Template pattern: underscores represent positions that must be hex digits
    // Pattern: "{XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}"
    static const char pattern[39] = "{XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}";

    for (int i = 0; i < 38; i++)
    {
        if (pattern[i] == 'X')
        {
            // Must be a hex digit (0-9, A-F, a-f)
            char c = str[i];
            if (!((c >= '0' && c <= '9') ||
                  (c >= 'A' && c <= 'F') ||
                  (c >= 'a' && c <= 'f')))
                return false;
        }
        else if (str[i] != pattern[i])
        {
            // Must match the literal character (dash, brace)
            return false;
        }
    }
    return true;
}