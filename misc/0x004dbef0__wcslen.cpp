// FUNC_NAME: wcslen
// Function address: 0x004dbef0
// Role: Wide character string length (wcslen implementation)

int wcslen(const short* str)
{
    int length = 0;
    if (str != nullptr)
    {
        while (*str != 0)
        {
            str++;
            length++;
        }
    }
    return length;
}