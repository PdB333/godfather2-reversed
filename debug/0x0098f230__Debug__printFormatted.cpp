//FUNC_NAME: Debug::printFormatted
void __thiscall Debug::printFormatted(int thisPtr, int param2, undefined4 param3)
{
    undefined4 formatBuffer;
    undefined2 formatBufferExtra;
    char *prefix;

    if (*(int *)(thisPtr + 0xc) == 0) {
        // Use default format string when width/flag is zero
        formatBuffer = DAT_00d91af0;   // +0x0: default format string (e.g., "$%s%0*u")
        formatBufferExtra = DAT_00d91af4; // +0x4: continuation of default format
    } else {
        // Build format string with variable width from field at +0xc
        formatString(&formatBuffer, 0x10, "$%%s%%0%uu", *(int *)(thisPtr + 0xc));
    }

    prefix = *(char **)(thisPtr + 0x10);
    if (prefix == (char *)0x0) {
        prefix = &DAT_0120546e; // Default empty prefix or category string
    }

    // Output the formatted message: param3 is likely a handle/stream,
    // formatBuffer is the format string, prefix is a category,
    // and param2 + *(int *)(thisPtr + 4) is the value to format
    outputString(param3, &formatBuffer, prefix, *(int *)(thisPtr + 4) + param2);
    return;
}