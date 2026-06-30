// FUNC_NAME: countAndSplitLines
// Function at 0x00605df0: Tokenizes a buffer by replacing newline (\n) and carriage return (\r) characters with null terminators,
// and counts the number of non-empty lines. The buffer is modified in place.
// Parameters: ESI = buffer pointer, EDI = buffer length (custom calling convention).
// Returns: number of lines found.
int countAndSplitLines(char* buffer, int bufferLength)
{
    bool inToken = false;
    int lineCount = 0;
    int offset = 0;

    if (bufferLength != 0)
    {
        do
        {
            if (buffer[offset] == '\n' || buffer[offset] == '\r')
            {
                // Replace newline/carriage return with null terminator
                buffer[offset] = '\0';
                inToken = false;
            }
            else if (!inToken)
            {
                // Start of a new line (non-whitespace character)
                lineCount++;
                inToken = true;
            }
            offset++;
        } while (offset < bufferLength);
    }
    return lineCount;
}