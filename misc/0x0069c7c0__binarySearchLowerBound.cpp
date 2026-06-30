// FUNC_NAME: binarySearchLowerBound
unsigned char* __cdecl binarySearchLowerBound(unsigned char* dataBase, unsigned char* dataEnd, unsigned char keyByte) {
    int count = (dataEnd - dataBase) >> 3; // number of 8-byte elements
    if (count > 0) {
        do {
            int midIndex = count / 2;
            unsigned char* midElement = dataBase + midIndex * 8;
            if (*midElement < keyByte) {
                dataBase = midElement + 8; // move past this element
                count = count - 1 - midIndex;
            } else {
                count = midIndex;
            }
        } while (count > 0);
    }
    return dataBase;
}