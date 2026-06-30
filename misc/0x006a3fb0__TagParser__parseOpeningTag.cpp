// FUNC_NAME: TagParser::parseOpeningTag
void __thiscall TagParser::parseOpeningTag(int *thisPtr, short *buffer)
{
    int offset;
    int tokenLen;

    // Search for the pattern (likely a tag start marker like '<')
    offset = findPattern(buffer, (short *)0x00d5d604);
    if ((offset < 0) || (buffer[offset] != 0x3c))  // 0x3c = '<'
    {
        // Error: tag not found or not '<'
        // Call the second virtual method of the error handler (offset +4 in vtable)
        (**(code **)(*(int *)thisPtr[1] + 4))();
        return;
    }

    // Read the character following '<' (e.g., tag name length or token)
    tokenLen = readTokenLen(buffer + offset);
    if (tokenLen != -1)
    {
        if (tokenLen != -2)
        {
            offset += tokenLen;
        }
        // Parse attributes or content of the tag
        int result = parseTagAttributes(buffer + offset, thisPtr, *thisPtr != 0, offset);
        if (-1 < result)
        {
            return;
        }
    }
    // Error handling
    handleParseError(offset);
    return;
}