// FUNC_NAME: CallbackManager::registerCallback

// Global static state used by this function
// _DAT_01226f54: static int s_initFlags;
// DAT_0122399c: static void* s_registeredCallback; // +0x0
// DAT_012239a0: static int s_registeredId;          // +0x0

void CallbackManager::registerCallback(void* callbackData, int callbackType)
{
    static int s_initFlags;      // _DAT_01226f54
    static void* s_registeredCallback; // DAT_0122399c
    static int s_registeredId;        // DAT_012239a0

    // One-time engine subsystem initialization
    if ((s_initFlags & 1) == 0) {
        s_initFlags |= 1;
        FUN_00484b10();      // EARS subsystem init
        atexit((void (*)(void))0x00d50760); // register cleanup handler
    }

    // Prepare callback data (likely assigns to a local handle or does some init)
    FUN_00484070(&callbackData);

    // Validate current registration state
    int currentId = s_registeredId;          // iVar1
    void* currentCallback = s_registeredCallback; // local_1c (implicit)
    if ((currentCallback == nullptr) || (currentCallback != &s_registeredCallback)) {
        FUN_00b97aea(); // handle uninitialized or mismatched state
    }

    // If the given callback type matches the previously recorded ID, store the new pair
    if (callbackType == currentId) {
        void* newCallback = callbackData; // local_1c
        int newType = callbackType;       // local_18
        FUN_00483f20(&s_registeredCallback, &newCallback);
    }
}