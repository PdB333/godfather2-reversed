// FUNC_NAME: createManagedObject

uint __thiscall createManagedObject(void* thisPtr, int arg0)
{
    uint result;
    char* stringPtr;
    uint stringHandle;
    char* localString;
    int hasString;
    void (*destroyFunc)(char*);

    sub_4D3BC0(thisPtr);  // Likely initialization of some base or common data
    sub_4D54C0();         // Some system setup or global state update
    result = sub_4D5900(1);  // Possibly get a global flag/state (e.g., "isInitialized")

    if (hasString != 0) {  // hasString is likely set by some earlier call (or as ECX)
        stringPtr = localString;
        if (localString == NULL) {
            stringPtr = (char*)&DATA_0120546e;  // Default string literal
        }
        stringHandle = sub_4DAFD0(stringPtr);  // Load or register string resource
        result = sub_4D9080(thisPtr, stringHandle, stringHandle);  // Register with object (two handles? likely same)
    }
    if (localString != NULL) {
        destroyFunc(localString);  // Release the temporary string
    }
    return result & 0xFFFFFF00;  // Mask low byte (type/status bits)
}