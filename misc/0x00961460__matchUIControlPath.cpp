// FUNC_NAME: matchUIControlPath

char matchUIControlPath(const char* path)
{
    // Compare against known UI control paths and return an ID (0-4) or 5 for unknown.
    // The paths correspond to dropdowns and a button in the "onco" UI layout.
    // Note: The first path has a leading '?' that is skipped in the comparison.

    // Check for "/onco/control_day/dropdown" (skipping leading '?' in literal)
    if (strncmp(path, "/onco/control_day/dropdown", 0x1b) == 0) // 0x1b = 27 chars
    {
        return 0;
    }

    // Check for "/onco/control_month/dropdown"
    if (strncmp(path, "/onco/control_month/dropdown", 0x1d) == 0) // 0x1d = 29 chars
    {
        return 1;
    }

    // Check for "/onco/control_year/dropdown"
    if (strncmp(path, "/onco/control_year/dropdown", 0x1c) == 0) // 0x1c = 28 chars
    {
        return 2;
    }

    // Check for "/onco/control_country/dropdown"
    if (strncmp(path, "/onco/control_country/dropdown", 0x1f) == 0) // 0x1f = 31 chars
    {
        return 3;
    }

    // Check for "/onco/buttons/button_0/button"
    if (strncmp(path, "/onco/buttons/button_0/button", 0x1e) == 0) // 0x1e = 30 chars
    {
        return 4;
    }

    // No match found
    return 5;
}