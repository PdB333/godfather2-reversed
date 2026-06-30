// FUNC_NAME: dispatchGameEvent
int dispatchGameEvent(int* objectTypePtr, int* eventData) {
    if (objectTypePtr == nullptr || eventData == nullptr) {
        return 0;
    }
    int eventType = eventData[0];         // +0
    int eventSubType = eventData[2];      // +8
    if (eventType == 0 || eventType == 0x48) {
        return 0;
    }
    if (eventSubType == 0 || eventSubType == 0x48) {
        return 0;
    }
    int adjustedSubType = eventSubType - 0x48;     // subtract offset constant
    int adjustedObjectType = *objectTypePtr - 0x13; // subtract offset constant
    executeAction(adjustedSubType, adjustedObjectType);
    if (*objectTypePtr == 0x15) { // object type 21
        bool specialFeatureActive = checkHashExistence(0xc4bc3ce7, 0);
        if (specialFeatureActive) {
            processSpecialAction(adjustedSubType);
        }
    }
    return 0;
}