// FUN_NAME: GameManager::processUIEvent
// Address: 0x006e4ec0
// This function processes a UI event on a given object, checking validity through a virtual call
// and then possibly forwarding to another handler with a global manager's member at offset 0x28b8.

extern GameManager* g_gameManager; // Global singleton, likely stored in ESI

void __thiscall GameManager::processUIEvent(void* uiObject)
{
    // uiObject is a pointer to some UI element or game object
    // At offset +0x100, there is a pointer to an internal object with a vtable
    void** internalObjPtr = reinterpret_cast<void**>(uiObject);
    void* internalObj = internalObjPtr[0x100 / sizeof(void*)]; // offset 0x100

    // Virtual function at vtable+0x10 (index 4 since 4-byte pointers)
    // Takes a magic hash (0x383225a1) and a reference to an int (initialized to 0)
    // Returns bool indicating if the event is valid
    typedef bool (__thiscall* QueryEventFunc)(void*, int, int*);
    QueryEventFunc queryEvent = reinterpret_cast<QueryEventFunc>( (*(int**)internalObj)[4] );

    int eventResult = 0;              // Output parameter for the query
    bool isValid = queryEvent(internalObj, 0x383225a1, &eventResult);

    if (isValid && g_gameManager != nullptr)
    {
        // Call another function with the original uiObject, the eventResult, and a member of g_gameManager at offset 0x28b8
        FUN_006e3e50(uiObject, eventResult, reinterpret_cast<char*>(g_gameManager) + 0x28b8);
    }
    return;
}