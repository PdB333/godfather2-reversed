// FUNC_NAME: EventManager::dispatchEvent
void EventManager::dispatchEvent(uint targetId, uint eventId, undefined4 *dataBuffer, undefined8 *extraData)
{
    uint *nodePtr;
    undefined4 highWord;
    int hashTableBase;
    undefined4 *copyBuffer;
    undefined8 eventData[2];
    undefined **callbackList;
    uint objectRef;
    undefined4 *dataCopy;
    undefined8 *extraDataCopy;
    undefined4 stackBuffer[16]; // Actually overwritten beyond array size, but used as 64-byte buffer
    
    hashTableBase = *(int *)(g_eventManager + 8); // g_eventManager at 0x01223398, offset +8 is hash table pointer
    objectRef = 0;
    
    // First lookup (seems unused, possibly a bug or decompiler artifact)
    nodePtr = *(uint **)(*(int *)(hashTableBase + 4) + (targetId % *(uint *)(hashTableBase + 8)) * 4);
    while ((nodePtr != (uint *)0x0 && (*nodePtr != targetId))) {
        nodePtr = (uint *)nodePtr[2];
    }
    
    // Second lookup using eventId to retrieve the object reference
    nodePtr = *(uint **)(*(int *)(hashTableBase + 4) + (eventId % *(uint *)(hashTableBase + 8)) * 4);
    while (true) {
        if (nodePtr == (uint *)0x0) {
            goto LAB_DISPATCH;
        }
        if (*nodePtr == eventId) {
            if ((nodePtr != (uint *)0x0) && (nodePtr + 1 != (uint *)0x0)) {
                objectRef = nodePtr[1]; // value associated with eventId
            }
            goto LAB_DISPATCH;
        }
        nodePtr = (uint *)nodePtr[2];
    }
    
LAB_DISPATCH:
    // Prepare data for dispatch
    eventData[0] = *extraData;
    eventData[1] = extraData[1];
    copyBuffer = stackBuffer;
    for (int i = 0x10; i != 0; i--) {
        *copyBuffer = *dataBuffer;
        dataBuffer++;
        copyBuffer++;
    }
    
    // Clear flag bit 3 at object+0x94
    *(uint *)(objectRef + 0x94) = *(uint *)(objectRef + 0x94) & 0xfffffff7; // Clear bit 3
    
    highWord = g_constantWord; // DAT_00e448cc, maybe some mask or flags
    // Write two 64-bit values into object at offsets 0x80 and 0x88
    // stackBuffer[12] and stackBuffer[13] are the last 8 bytes of the copied data
    *(ulonglong *)(objectRef + 0x80) = CONCAT44(stackBuffer[13], stackBuffer[12]); // local_20, uStack_1c
    *(ulonglong *)(objectRef + 0x88) = CONCAT44(highWord, stackBuffer[14]); // uStack_18, highWord from global
    
    FUN_0044f770(objectRef, 0); // Possibly setObjectState(objectRef, 0)
    dataCopy = stackBuffer;
    extraDataCopy = &eventData[0];
    callbackList = &PTR_LAB_00d92224; // Global callback function pointer list
    FUN_0049f9b0(&callbackList); // Invoke callback with parameters
}