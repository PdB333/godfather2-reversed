// Xbox PDB: EARS::Apt::APT720pNameHelper::Is720pName
// FUNC_NAME: is720pAsset
// Address: 0x005be2c0
// Checks if a filename ends with "_720p.apx" or "_720p" (case-insensitive).
// Likely used for 720p resolution asset detection.

#include <cstring>

bool is720pAsset(const char* name)
{
    // Find length using manual scan
    const char* scan = name;
    while (*scan != '\0')
        ++scan;
    int len = scan - name; // length excluding null

    // Check for "_720p.apx" (9 characters)
    if (len > 9)
    {
        if (_stricmp(name + len - 9, "_720p.apx") == 0)
            return true;
    }

    // Check for "_720p" (5 characters)
    if (len > 5)
    {
        if (_stricmp(name + len - 5, "_720p") == 0)
            return true;
    }

    return false;
}