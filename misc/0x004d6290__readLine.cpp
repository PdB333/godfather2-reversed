// FUNC_NAME: readLine
bool readLine(char *outBuffer, int *outEndOffset, uint maxLength)
{
    // Allocate internal line buffer (parameters likely: number of lines, flags)
    char *buffer = (char *)allocateBuffer(1, 0); // FUN_004d5e10
    // Read next line from buffer; returns pointer to end (newline/null) and stores it via outEndOffset
    char *endPtr = (char *)readLineInternal(buffer, 1, (int **)&outEndOffset); // FUN_004d5fd0
    *outEndOffset = (int)endPtr;

    // Compute line length (end - start)
    size_t length = endPtr - buffer;

    // Cap length to fit output buffer (leave room for null terminator)
    if ((maxLength <= length) && (maxLength != 0)) {
        length = maxLength - 1;
    }

    if (length != 0) {
        strncpy(outBuffer, buffer, length);
        outBuffer[length] = '\0';
        return true; // line copied successfully
    }

    // No data read
    outBuffer[0] = '\0';
    return false;
}