// FUNC_NAME: mapEnumToIndex
// Function address: 0x00875b40
// Role: Converts an enum value (10-13) to an index (0-3), returns -1 for unknown.
int mapEnumToIndex(int* enumValue)
{
    int result = -1;
    switch (*enumValue)
    {
    case 10:
        return 0;
    case 11:
        return 1;
    case 12:
        return 2;
    case 13:
        result = 3;
        break;
    }
    return result;
}