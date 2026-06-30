// FUNC_NAME: EARSObject::getValidName
// Address: 0x00556e60
// Role: Returns a non-empty name string from internal object ID, or null if invalid/empty.

char* __thiscall EARSObject::getValidName(void) {
    // +0x40: internal object identifier (could be an ID or pointer to a string)
    int objectId = *(int*)((char*)this + 0x40); 

    if (objectId != 0) {
        // Global name management singleton (DAT_0113dfc8)
        void* nameManager = *(void**)0x0113dfc8;
        // Get the name conversion interface (vtbl offset +0x14)
        void* nameInterface = (*(void* (__stdcall**)())nameManager)();
        // Convert objectId to a string index using the interface (vtbl offset +0x10)
        uint nameIndex = (*(uint (__thiscall*)(void*, int))nameInterface)(nameInterface, objectId);
        // Retrieve the actual string into a stack buffer
        char tempBuffer[256]; // assumed size, could be different
        char* nameStr = (char*)FUN_00ab06f0(tempBuffer, nameIndex);
        if (*nameStr == '\0') {
            return 0; // string is empty, return null
        }
    }
    // Return the pointer stored at +0x40 (original object name string)
    return *(char**)((char*)this + 0x40);
}