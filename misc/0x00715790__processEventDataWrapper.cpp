// FUNC_NAME: processEventDataWrapper
void processEventDataWrapper(void* sourceObj, int param2, int param3) {
    char eventData[12]; // 12-byte buffer for event context (e.g., position, ID)
    getEventData(sourceObj, eventData); // fill buffer from source
    dispatchEvent(eventData, param2, param3, sourceObj); // handle event with additional params
}