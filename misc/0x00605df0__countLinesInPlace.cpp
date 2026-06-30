// FUNC_NAME: countLinesInPlace
// Function at 0x00605df0: Counts number of lines in a buffer, replacing newline/carriage return characters with null terminators.
// Parameters: buffer pointer (ESI), length (EDI)
// Returns: number of lines (words) found.

int countLinesInPlace(char* buffer, uint length)
{
    bool inLine = false;
    int lineCount = 0;
    uint index = 0;

    if (length != 0) {
        do {
            char ch = buffer[index];
            if (ch == '\n' || ch == '\r') {
                buffer[index] = '\0'; // Replace newline/CR with null terminator
                inLine = false;
            }
            else if (!inLine) {
                lineCount++;
                inLine = true;
            }
            index++;
        } while (index < length);
    }
    return lineCount;
}