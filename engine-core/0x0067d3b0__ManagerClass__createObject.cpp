// FUNC_NAME: ManagerClass::createObject
void ManagerClass::createObject(void* thisPtr, CreateParams* params) {
    // Get the singleton manager pointer from a global function.
    ManagerVTable** manager = (ManagerVTable**)GetManagerSingleton();
    // Prepare creation parameters.
    CreateParams localParams;
    localParams.type = 2;        // Object type constant
    localParams.flags = 0x10;    // Some creation flags
    localParams.extra = 0;       // Reserved
    // Call the first virtual function of the manager (likely a creation/initialization method).
    (*(void(__thiscall*)(void*, CreateParams*))(*manager))(thisPtr, &localParams);
}