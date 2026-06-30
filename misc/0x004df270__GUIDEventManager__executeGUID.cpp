// FUNC_NAME: GUIDEventManager::executeGUID
uint32_t* GUIDEventManager::executeGUID(uint32_t* outResult, uint32_t* guid4, uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
    // Check if the GUID is non-zero (4 DWORDs)
    if (guid4[0] != 0 || guid4[1] != 0 || guid4[2] != 0 || guid4[3] != 0) {
        // Get a pointer to the global event manager handle
        int* handlePtr = (int*)getEventManager();  // FUN_004e0d30 - returns pointer to handle
        if (handlePtr != nullptr) {
            int eventObj = *handlePtr;  // Dereference handle to get actual object pointer
            if (eventObj != 0) {
                // Initialize logging once (string is a GUID)
                if ((g_GUIDLogFlag & 1) == 0) {
                    g_GUIDLogFlag |= 1;
                    logGUID("{BDFF6379-6379-BDFF-7963-FFBD7963FFBD}");  // FUN_004d9500
                }
                // Compare the input GUID with a stored global GUID
                if (g_StoredGUID[0] == guid4[0] &&
                    g_StoredGUID[1] == guid4[1] &&
                    g_StoredGUID[2] == guid4[2] &&
                    g_StoredGUID[3] == guid4[3]) {
                    // Set flag at offset 0x14 in the event object
                    *(uint32_t*)(eventObj + 0x14) |= 0x20;
                }
                // Forward the call to another handler with the original arguments
                executeGUIDHandler(eventObj, arg1, arg2, arg3);  // FUN_004df210
                return outResult;
            }
        }
    }
    // Failure case: clear output
    *outResult = 0;
    return outResult;
}