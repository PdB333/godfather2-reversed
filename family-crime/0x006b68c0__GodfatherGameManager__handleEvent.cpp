// FUNC_NAME: GodfatherGameManager::handleEvent
void __thiscall GodfatherGameManager::handleEvent(int this, int eventId, undefined4 eventData1, int eventData2, undefined4 eventData3)
{
    char isSpecial;
    undefined4 objectId;
    int randomValue;

    // Get object from internal ID at +0x40
    objectId = getObjectFromId(*(undefined4 *)(this + 0x40));
    preProcessEvent(objectId);

    // Dispatch the event with its parameters
    objectId = getObjectFromId(eventId);
    dispatchEvent(objectId, eventId, eventData1, eventData2, eventData3);

    if (eventData2 == 0) {
        // Check if we are in a specific state (flags at +0xc4 and +0xc0)
        if ((*(int *)(this + 0xc4) == 1) && (*(int *)(this + 0xc0) != 0)) {
            randomValue = getRandomNumber();
            if (randomValue != 0) {
                randomValue = getRandomNumber();
                // Compare with a known event hash (0x637b907)
                if ((randomValue != 0x637b907) && (eventId == 0x637b907)) {
                    isSpecial = checkSpecialCondition();
                    if (isSpecial != '\0') {
                        logDebugMessage(0x9baf024);
                    }
                }
            }
        }
        // Release event data stored at +0x38
        releaseEventData(*(undefined4 *)(this + 0x38));
    }

    // Branch based on flag at +0xfc
    if (*(int *)(this + 0xfc) != 0) {
        processNormal();
        return;
    }
    processFallback();
    return;
}