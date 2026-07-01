// FUNC_NAME: BinaryStreamLoader::parseFromStream
void __thiscall BinaryStreamLoader::parseFromStream(int this, void* inputStream)
{
    char isStreamDone;
    int dataType;
    int dataValue;

    // Initialize the stream reader
    initStream(inputStream);
    // Set stream magic number (0x77032ad0)
    setStreamMagic(inputStream, 0x77032ad0);

    // Loop until all data is processed
    isStreamDone = isStreamFinished();
    while (!isStreamDone) {
        // Advance to next token
        advanceStream();

        // Read data type identifier (0-3)
        dataType = readDataType();

        switch (dataType) {
        case 0:
        case 1: {
            // For types 0 and 1, read a data value and process it
            advanceStream();
            dataValue = readDataValue();
            processDataValue(dataValue);
            break;
        }
        case 2: {
            // Type 2: read pointer and store at offset +0x70
            int streamState = advanceStream();
            *(int*)(this + 0x70) = *(int*)(streamState + 8);
            break;
        }
        case 3: {
            // Type 3: read pointer and store at offset +0x74
            int streamState = advanceStream();
            *(int*)(this + 0x74) = *(int*)(streamState + 8);
            break;
        }
        }

        // End of current token
        finalizeToken();

        isStreamDone = isStreamFinished();
    }

    // If a global debug flag is set, perform additional initialization
    if (g_debugFlag != 0) {
        postInitialize(this);
    }
}