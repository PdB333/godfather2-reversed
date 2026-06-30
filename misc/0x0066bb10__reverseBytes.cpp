// FUNC_NAME: reverseBytes
// Function address: 0x0066bb10
// Purpose: Reverses a byte buffer in-place (standard in-place reversal)
// Parameters:
//   int count     - number of bytes (passed in EAX)
//   char* buffer  - pointer to buffer (passed in ESI)

void __cdecl reverseBytes(int count, char* buffer)
{
    int left = 0;
    int right = count - 1;

    if (0 < right)
    {
        do
        {
            char temp = buffer[left];
            buffer[left] = buffer[right];
            buffer[right] = temp;

            left++;
            right--;
        } while (left < right);
    }
}