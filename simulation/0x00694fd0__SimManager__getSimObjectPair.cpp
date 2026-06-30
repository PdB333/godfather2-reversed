// FUNC_NAME: SimManager::getSimObjectPair
void __thiscall SimManager::getSimObjectPair(int thisPtr, int *outPair, int paramID) {
    // FUN_006948e0: likely retrieves an ID from the parameter (e.g., a hash or enum)
    int computedID = getParamID(paramID);  
    // +0x4: stored identifier (e.g., current state or object ID)
    int storedID = *(int *)(thisPtr + 0x4); 
    if (computedID != storedID) {
        // FUN_004d4b20: checks if an object at an index (computedID + 0xc) is valid
        int isValid = isValidObjectAtIndex(computedID + 0xc);
        if (isValid >= 0) { // valid object exists
            outPair[0] = thisPtr;
            outPair[1] = computedID;
            return;
        }
    }
    outPair[0] = thisPtr;
    outPair[1] = storedID;
}