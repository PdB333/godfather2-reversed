// FUNC_NAME: DataTable::getElementByIndex
unsigned int DataTable::getElementByIndex(int index) {
    unsigned int result = 0;

    // +0x34: pointer to index table (contains ushort offsets at +0x0E)
    char* indexTable = *(char**)(this + 0x34);
    // +0x38: pointer to data array (array of 4-byte elements)
    unsigned int* dataArray = *(unsigned int**)(this + 0x38);

    if (indexTable != NULL && dataArray != NULL) {
        // Index table has a header of 0x0E bytes, then an array of ushort indices
        unsigned short dataIndex = *(unsigned short*)(indexTable + 0x0E + index * 2);
        result = dataArray[dataIndex];
    }

    return result;
}