// FUNC_NAME: LocalizationManager::outputLocalizedString
void LocalizationManager::outputLocalizedString(uint stringId, void* context, OutputBuffer* outputBuffer) {
    int keyBuffer[3];
    void (*callbackFunc)(int) = nullptr;
    StringInfo* stringInfo = (StringInfo*)getStringInfo(keyBuffer, stringId);
    char* stringPtr = stringInfo ? (char*)stringInfo->text : (char*)"\0";
    if (!stringPtr) {
        stringPtr = (char*)0x0120546e; // default empty string
    }
    printString(stringPtr);
    if (keyBuffer[0] != 0) {
        callbackFunc(keyBuffer[0]);
    }
    if (outputBuffer->argumentCount != 1) {
        int hashIndex = hashTableSize * 8;
        keyBuffer[0] = (keyBuffer[0] & 0x00FFFFFF) | ((stringId & 0xFF) << 24);
        keyBuffer[1] = 0;
        char* lookupResult = (char*)hashTableFind(&hashTableArray, &hashTableArray + hashIndex, keyBuffer, 0);
        if (lookupResult != (&hashTableArray + hashIndex)) {
            int entryId = *(int*)(lookupResult + 4);
            if (entryId != 0) {
                char* fallbackString = (char*)getStringFromHashEntry(entryId);
                printString(fallbackString);
            }
        }
    }
}