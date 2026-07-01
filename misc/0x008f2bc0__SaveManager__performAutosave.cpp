// FUNC_NAME: SaveManager::performAutosave

void SaveManager::performAutosave(undefined2 **outputBufferPtr)
{
    char *formattedString = nullptr;
    int stringLength = 0;
    int someFlag = 0;
    void (*stringDestructor)(char *) = nullptr;
    undefined2 *outputBuffer = nullptr;
    int outputBufferSize = 0;
    void (*bufferDestructor)(undefined2 *) = nullptr;

    // Get a unique timestamp/ID (likely game session ID)
    uint timestamp = GetTimeStamp(0xffffffff);

    // Format the autosave filename: "GF2-<timestamp>-"
    FormatString(&formattedString, "GF2-%s-", timestamp);

    // Allocate memory for the output buffer? (maybe initializes a string builder)
    AllocateBuffer();

    // Append the literal "autosave" to the filename
    StringCopy("autosave");

    // Compute length of the formatted string
    char *endPtr = formattedString;
    if (formattedString == nullptr) {
        endPtr = &DAT_0120546e; // default empty string
    }
    char *temp = endPtr;
    while (*temp != '\0') {
        temp++;
    }
    int length = (int)(temp - (endPtr + 1));

    // Write the formatted string (filename) to some output (log file?)
    WriteToFile(endPtr, length);

    // If the output buffer pointer is not pointing to our local buffer (debug check)
    if (outputBufferPtr != &outputBuffer) {
        undefined2 *buf = outputBuffer;
        if (outputBuffer == nullptr) {
            buf = &DAT_00e2df14; // default buffer
        }
        // Write additional data to the buffer (maybe the actual save data)
        WriteBufferData(buf, 0, outputBufferSize);
    }

    // Destructor calls for RAII cleanup
    if (outputBuffer != nullptr) {
        bufferDestructor(outputBuffer);
    }
    if (formattedString != nullptr) {
        stringDestructor(formattedString);
    }
}