// FUNC_NAME: stripApxExtension
// Function at 0x005be330: Strips the ".apx" extension from a filename (case-insensitive),
// e.g., "file.apx" becomes "file". The first parameter (ECX) is unused in this function;
// it may be an artifact of the fastcall convention used by a static or standalone function.

void __fastcall stripApxExtension(char* path)
{
    // Compute length with manual loop (same as original binary)
    char* ptr = path;
    do {
        char current = *ptr;
        ptr++;
    } while (current != '\0');
    int len = (ptr - path) - 1; // length excluding null terminator

    // Check if the last 4 characters form case-insensitive ".apx"
    if (len > 4 &&
        path[len - 4] == '.' &&
        (path[len - 3] == 'a' || path[len - 3] == 'A') &&
        (path[len - 2] == 'p' || path[len - 2] == 'P') &&
        (path[len - 1] == 'x' || path[len - 1] == 'X'))
    {
        path[len - 4] = '\0'; // Strip the extension
    }
}