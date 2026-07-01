// FUNC_NAME: FrontendManager::loadFrontendAssets
void FrontendManager::loadFrontendAssets(void) {
    // +0x00: pointer to string or null
    undefined2 *szLoadingLabel = nullptr;
    // +0x00: unused/reserved
    undefined4 unused_0 = 0;
    // +0x00: some handle
    undefined4 handle_0 = 0;
    // +0x00: pointer to string buffer
    undefined1 *szPathBuffer = nullptr;
    // +0x00: size
    undefined4 bufferSize = 0;
    // +0x00: capacity
    undefined4 bufferCapacity = 0;
    // +0x00: function pointer for cleanup
    code *pCleanupFunc = nullptr;
    // +0x00: another pointer
    undefined1 *pMem = nullptr;
    // +0x00: function pointer for cleanup
    code *pAnotherCleanup = nullptr;
    // Buffer for 320 bytes
    undefined1 szLargeBuffer[320];
    undefined4 returnValue; // store FUN_008f2c90 result

    // Initialize the string pointer (maybe a resource path)
    FUN_008f3af0(&szLoadingLabel);
    // If null, use default string
    undefined2 *pLabel = szLoadingLabel;
    if (szLoadingLabel == nullptr) {
        pLabel = (undefined2 *)&DAT_00e2df14; // Default string "loading"?
    }
    FUN_004d4570(pLabel); // Set loading label

    // Hash lookup for something (0x693a8b8f might be "frontend")
    undefined4 hashOut;
    undefined1 hashType;
    hashOut = 0;
    FUN_006039d0(0x693a8b8f, &hashOut, &hashType);
    FUN_004d3bc0(hashOut); // Use the hash result

    // Get a return value and call another initializer
    returnValue = FUN_008f2c90();
    FUN_008f2530();

    // Initialize two subsystems with default path string (&DAT_0120546e maybe "fx")
    undefined1 *pPath = szPathBuffer;
    if (szPathBuffer == nullptr) {
        pPath = &DAT_0120546e;
    }
    FUN_008f2030(pPath); // e.g., load particle system

    pPath = pMem;
    if (pMem == nullptr) {
        pPath = &DAT_0120546e; // same default
    }
    FUN_008f2050(pPath); // e.g., load audio

    // Store the return value for later
    local_418 = returnValue; // Might be a timer or handle

    // Prepare a large buffer (e.g., for font/text)
    FUN_008f3f10(szLargeBuffer, 0); // Clear or initialize buffer

    // Execute frame update
    FUN_008f2020(); // e.g., render a single frame

    // Cleanup if pointers were allocated
    if (pMem != nullptr) {
        (*pAnotherCleanup)(pMem);
    }
    if (szPathBuffer != nullptr) {
        (*pCleanupFunc)(szPathBuffer);
    }
    if (szLoadingLabel != nullptr) {
        (*(code *)(&pcStack_56c))(szLoadingLabel);
    }
    return;
}