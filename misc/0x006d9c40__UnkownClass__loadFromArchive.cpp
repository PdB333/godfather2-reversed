// FUNC_NAME: UnkownClass::loadFromArchive
// Address: 0x006d9c40
// Identified role: Parses an archive stream to populate four fields at offsets 0x60, 0x64, 0x68, 0x6c.

void __thiscall UnkownClass::loadFromArchive(int thisPtr, undefined4 stream) {
    char hasMore;
    int element;
    int type;

    // Open the archive with a magic identifier (0x3243a9f0)
    DataStream_Open(stream, 0x3243a9f0);

    hasMore = DataStream_HasNext(stream);
    while (hasMore == 0) {
        // Advance to next element in stream
        DataStream_Next(stream);
        type = DataStream_GetType(stream);
        switch (type) {
        case 0:
            // Read value from element at offset +8 and store to this+0x60
            element = DataStream_Next(stream);
            *(int *)(thisPtr + 0x60) = *(int *)(element + 8);
            break;
        case 1:
            // Read value and store to this+0x64 (100 decimal)
            element = DataStream_Next(stream);
            *(int *)(thisPtr + 100) = *(int *)(element + 8);
            break;
        case 2:
            // Read value and store to this+0x68
            element = DataStream_Next(stream);
            *(int *)(thisPtr + 0x68) = *(int *)(element + 8);
            break;
        case 3:
            // Read value and store to this+0x6c
            element = DataStream_Next(stream);
            *(int *)(thisPtr + 0x6c) = *(int *)(element + 8);
            break;
        }
        // Finish processing current element
        DataStream_CloseElement(stream);
        hasMore = DataStream_HasNext(stream);
    }
    // Close the archive
    DataStream_Close(stream);
}