// FUNC_NAME: PropertySet::deserialize
// Address: 0x008ff660
// Role: Reads a sequence of typed properties from a binary stream and populates member fields at offsets 0x50,0x54,0x58,0x60,0x68.
// The stream is initialized with a hash (0xa8631a6f) and then iterated until end.

void __thiscall PropertySet::deserialize(int thisPtr, void* dataStream)
{
    char hasMore;
    int type;
    int intValue;
    int stringHandle;
    int nextInt;
    
    // Initialize stream reader and set its type/version
    StreamReader::attach(dataStream);
    StreamReader::setType(dataStream, 0xa8631a6f);
    
    hasMore = StreamReader::hasMore(dataStream);
    do {
        if (hasMore != '\0') {
            return;
        }
        // Advance to next property
        StreamReader::advance(dataStream);
        type = StreamReader::readType(dataStream);
        switch(type) {
        case 0:
            // Read integer field at offset 0x50
            nextInt = StreamReader::readInt(dataStream);
            *(int *)(thisPtr + 0x50) = *(int *)(nextInt + 8);
            break;
        case 1:
            // Read integer field at offset 0x54
            nextInt = StreamReader::readInt(dataStream);
            *(int *)(thisPtr + 0x54) = *(int *)(nextInt + 8);
            break;
        case 2:
            // Read string field at offset 0x58
            StreamReader::readInt(dataStream);
            stringHandle = StreamReader::readString(dataStream);
            setStringFromHandle(thisPtr + 0x58, stringHandle);
            break;
        case 3:
            // Read string field at offset 0x60
            StreamReader::readInt(dataStream);
            stringHandle = StreamReader::readString(dataStream);
            setStringFromHandle(thisPtr + 0x60, stringHandle);
            break;
        case 4:
            // Read string field at offset 0x68
            StreamReader::readInt(dataStream);
            stringHandle = StreamReader::readString(dataStream);
            setStringFromHandle(thisPtr + 0x68, stringHandle);
            break;
        }
        // Move to next property
        StreamReader::finishProperty(dataStream);
        hasMore = StreamReader::hasMore(dataStream);
    } while( true );
}