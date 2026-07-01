// FUNC_NAME: DataReader::parseProperties

void __thiscall DataReader::parseProperties(int thisPtr, void* stream)
{
    char hasMore;
    int itemPtr;
    int itemType;

    DataReader::open(stream);                     // Initialize reader for stream
    DataReader::setPropertyHash(stream, 0x925e3b44); // Look for property with specific hash

    hasMore = DataReader::hasMoreItems();         // Check if more items available
    while (hasMore == 0) {
        DataReader::advance();                    // Move to next item
        itemType = DataReader::getItemType();     // Get type of current item
        if (itemType == 0) {
            itemPtr = DataReader::getNextItem();  // Get data pointer for item
            *(void**)(thisPtr + 0x64) = *(void**)(itemPtr + 8); // Assign to member at +0x64
        }
        else if (itemType == 1) {
            itemPtr = DataReader::getNextItem();
            *(void**)(thisPtr + 0x68) = *(void**)(itemPtr + 8); // Assign to member at +0x68
        }
        else if (itemType == 2) {
            itemPtr = DataReader::getNextItem();
            *(void**)(thisPtr + 0x6C) = *(void**)(itemPtr + 8); // Assign to member at +0x6C
        }
        DataReader::next();                       // Advance to next item
        hasMore = DataReader::hasMoreItems();
    }
}