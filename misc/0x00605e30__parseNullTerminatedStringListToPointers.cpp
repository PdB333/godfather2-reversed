// FUNC_NAME: parseNullTerminatedStringListToPointers
void parseNullTerminatedStringListToPointers(char* stringList, char** outPtrArray, uint listLength)
{
    // This function scans a buffer containing multiple null-terminated strings sequentially.
    // It populates outPtrArray with pointers to the start of each non-empty string.
    // If a string is empty (i.e., a null byte encountered when not inside a string), 
    //   it is skipped. The array is filled in order of appearance.
    bool insideString = false;
    uint index = 0;
    if (listLength == 0) return;
    do {
        if (stringList[index] == '\0') {
            insideString = false;
        } else if (!insideString) {
            *outPtrArray = &stringList[index];
            outPtrArray++;
            insideString = true;
        }
        index++;
    } while (index < listLength);
}