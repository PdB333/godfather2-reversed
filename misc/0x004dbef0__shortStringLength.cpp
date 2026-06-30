// FUNC_NAME: shortStringLength

// Reconstructed strlen for 16-bit (wide) strings.
// Iterates over null-terminated array of short ints, returns count of elements before the zero terminator.
int shortStringLength(short* str)
{
    int length = 0;
    if (str != nullptr)
    {
        while (*str != 0)
        {
            ++str;
            ++length;
        }
    }
    return length;
}