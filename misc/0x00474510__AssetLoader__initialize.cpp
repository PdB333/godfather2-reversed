// FUNC_NAME: AssetLoader::initialize
bool __thiscall AssetLoader::initialize(void) {
    // Check if already initialized (+0xe8 flag)
    bool alreadyInitialized = *(int*)(this + 0xe8) != 0;
    if (alreadyInitialized) {
        return alreadyInitialized;
    }

    // Attempt to load the sub-asset at +0x6c
    int loaderResult = loadSubObject(this + 0x6c, 0, 0); // FUN_00455f50
    if (loaderResult == 0) {
        return false;
    }

    // Set up the vtable/callback at +0x7c
    void** vtablePtr = (void**)(this + 0x7c);
    char vtableInitResult = allocateVtable(vtablePtr, loaderResult); // FUN_004a84d0
    if (vtableInitResult == '\0') {
        return false;
    }

    // Store self-reference at +0xe4
    *(int*)(this + 0xe4) = (int)this;

    // Assign the vtable base address
    *vtablePtr = &vtable_004747a0; // Placeholder address

    // Temporary string buffer (custom counted string)
    struct CustomString {
        char* data;   // +0x00
        int length;   // +0x04
        int capacity; // +0x08
        void (*destructor)(char*); // +0x0c
    } strBuf;
    strBuf.data = 0;
    strBuf.length = 0;
    strBuf.capacity = 0;
    strBuf.destructor = 0;

    // Get a string identifier from the loader result
    char gotName = getStringName(&strBuf, loaderResult, 0); // FUN_004a8460
    if (gotName != '\0') {
        char* namePtr = strBuf.data;
        if (namePtr == 0) {
            namePtr = defaultNameString; // DAT_0120546e
        }
        // Register this asset with the name
        char registerResult = registerAsset(this + 0xe8, namePtr, vtablePtr); // FUN_005e2a50
        bool success = true;
        if (registerResult != '\0') goto cleanup;
    }
    success = false;

cleanup:
    // Free the temporary string buffer if allocated
    if (strBuf.data != 0) {
        strBuf.destructor(strBuf.data);
    }
    return success;
}