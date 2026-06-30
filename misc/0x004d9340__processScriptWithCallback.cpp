// FUNC_NAME: processScriptWithCallback
uint32_t processScriptWithCallback(uint32_t param1)
{
    uint32_t result;
    const char* contentStr;
    uint32_t processedStr;
    int hasContent;
    void (*callbackFunc)(const char*);

    // Initialize internal state (likely sets contentStr, hasContent, callbackFunc)
    initObject(this);                          // FUN_004d3bc0
    setupEnvironment();                        // FUN_004d54c0
    result = checkFlag(1);                     // FUN_004d5900

    if (hasContent != 0) {
        const char* strToProcess = contentStr;
        if (contentStr == nullptr) {
            strToProcess = (const char*)&DAT_0120546e; // Default string "?/"
        }
        processedStr = processString(strToProcess);   // FUN_004dafd0
        result = finalizeObject(param1, processedStr, processedStr); // FUN_004d9080
    }

    if (contentStr != nullptr) {
        callbackFunc(contentStr);               // Execute stored function pointer
    }

    return result & 0xffffff00;
}