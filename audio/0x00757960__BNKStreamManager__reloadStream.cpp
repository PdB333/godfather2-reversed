// FUNC_NAME: BNKStreamManager::reloadStream
// Function address: 0x00757960
// Role: Reloads a BNK stream object; checks global audio state, releases old object, creates new one if allowed, registers it with the stream handle, then cleans up the stream handle.
// Offsets:
//   +0x108 (int): Stream handle (identifier)
//   +0x10c (void*): Pointer to a BNK stream object (likely a class with virtual release(int))

void __fastcall BNKStreamManager::reloadStream(int this) {
    int* pStreamHandle = (int*)(this + 0x108);  // +0x108
    void** ppStreamObject = (void**)(this + 0x10c); // +0x10c
    bool bGlobalState1;
    bool bGlobalState2;
    int newObject;
    int uVar;

    if (*pStreamHandle != 0) {
        bGlobalState1 = isAudioSystemReady(0); // Check if audio system is ready (0 = main thread)
        if (bGlobalState1) {
            // Release and delete the existing stream object if present
            if (*ppStreamObject != 0) {
                // Call virtual release function with argument 1 (likely "force release")
                (*(void (__thiscall**)(void*, int))*ppStreamObject)(*ppStreamObject, 1);
                if (*ppStreamObject != 0) {
                    operatorDelete(ppStreamObject); // Delete the object, but does not null the pointer
                    *ppStreamObject = 0;
                }
            }
            bGlobalState2 = isStreamReloadAllowed(); // Check if stream reload is permitted
            if (bGlobalState2) {
                newObject = operatorNew(0x18); // Allocate 0x18 bytes
                if (newObject == 0) {
                    uVar = 0;
                } else {
                    uVar = createStreamObject(); // Construct a new stream object, returns handle or pointer
                }
                initStreamObject(uVar); // Initialize the new object
                bGlobalState2 = registerStreamObject(*pStreamHandle, *ppStreamObject); // Register new object with the stream handle
                if ((bGlobalState2) && (*ppStreamObject != 0)) {
                    cleanupSomething(); // Global cleanup (no arguments)
                }
            }
            releaseStreamHandle(*pStreamHandle); // Release the stream handle
            *pStreamHandle = 0; // Clear the handle
        }
    }
}