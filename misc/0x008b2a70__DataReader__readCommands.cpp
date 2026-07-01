// FUNC_NAME: DataReader::readCommands

void __thiscall DataReader::readCommands(int thisPtr, undefined4 param_2)
{
    char isDone;
    int commandType;
    undefined4 stringValue;

    // Initialize the reader with the given data source
    initializeReader(param_2);
    // Set a hash identifier (likely a magic number or string hash)
    setHash(param_2, 0x4520a86a);

    isDone = isReaderDone();
    while (isDone == '\0') {
        // Advance to next item in the stream
        advanceToNext();
        commandType = getCommandType();
        if (commandType == 0) {
            // Command 0: read an integer value into offset +0x64 (100)
            int currentItem = advanceToNext(); // Note: advanceToNext returns pointer to current item?
            *(int *)(thisPtr + 100) = *(int *)(currentItem + 8);
        }
        else if (commandType == 1) {
            // Command 1: read an integer value into offset +0x68
            int currentItem = advanceToNext();
            *(int *)(thisPtr + 0x68) = *(int *)(currentItem + 8);
        }
        else if (commandType == 2) {
            // Command 2: read a string value into offset +0x6c
            advanceToNext();
            stringValue = getStringValue();
            setString(thisPtr + 0x6c, stringValue);
        }
        // Move to next command
        advanceToNext();
        isDone = isReaderDone();
    }
    return;
}