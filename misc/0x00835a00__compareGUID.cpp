// FUNC_NAME: compareGUID
// Function address: 0x00835a00
// Compares two 192-bit GUIDs (6 x uint32) lexicographically.
// Returns 1 if a < b, 0 otherwise.
int compareGUID(const uint32_t* a, const uint32_t* b)
{
    // Compare each 32-bit word from most significant to least
    if (a[0] < b[0]) return 1;
    if (a[0] > b[0]) return 0;

    if (a[1] < b[1]) return 1;
    if (a[1] > b[1]) return 0;

    if (a[2] < b[2]) return 1;
    if (a[2] > b[2]) return 0;

    if (a[3] < b[3]) return 1;
    if (a[3] > b[3]) return 0;

    if (a[4] < b[4]) return 1;
    if (a[4] > b[4]) return 0;

    if (a[5] < b[5]) return 1;
    // If all equal, return 0 (not less)
    return 0;
}