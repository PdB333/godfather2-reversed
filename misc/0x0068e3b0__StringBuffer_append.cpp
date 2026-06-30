// FUNC_NAME: StringBuffer_append
// Function address: 0x0068e3b0
// Appends a null-terminated string to a buffer with capacity tracking.
// param_1: source string to append
// param_2: if non-zero, clears the buffer before appending
// param_3: pointer to a 3-int struct: buffer pointer, current offset, total capacity
// Returns 1 on success, 0 if source is null.

int StringBuffer_append(char *source, char clearBeforeAppend, int *bufferInfo)
{
    char cVar1;
    char *pcVar2;

    if (source != (char *)0x0)
    {
        if (clearBeforeAppend != '\0')
        {
            _memset((void *)*bufferInfo, 0, bufferInfo[2]);
        }
        pcVar2 = source;
        do
        {
            cVar1 = *pcVar2;
            pcVar2 = pcVar2 + 1;
        } while (cVar1 != '\0');
        _strncpy_s((char *)(*bufferInfo + bufferInfo[1]), bufferInfo[2] - bufferInfo[1], source,
                   (int)pcVar2 - (int)(source + 1));
        bufferInfo[1] = bufferInfo[1] + ((int)pcVar2 - (int)(source + 1));
        return 1;
    }
    return 0;
}