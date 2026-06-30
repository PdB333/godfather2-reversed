// FUNC_NAME: Model::loadResource

bool __thiscall Model::loadResource(int this, int loadMode, char isInitialLoad) {
    int *resourceHandle;
    uint colorData;
    undefined1 *namePtr;
    int lookupHandle;
    int *existingHandle;
    char *selectedName;
    bool loadSuccess;
    int tempHandle;
    float colorR;
    float colorG;
    float colorB;
    float colorA;
    char formattedName[64]; // overlaps local_90
    float colorComponents[4]; // used for setColor
    char buffer[76]; // transformation data

    // --- Early exit for non-load calls (e.g., unload) ---
    if (isInitialLoad == '\0') {
        if (loadMode != 0) {
            if (loadMode == 1) {
                unloadResource(); // FUN_004df650
            }
            return true;
        }
        unloadResource();
        return true;
    }

    // --- Initialize color/transform defaults from global ---
    // _DAT_00d5780c is likely a default color (white) or identity matrix
    colorComponents[0] = _DAT_00d5780c; // R
    colorComponents[1] = _DAT_00d5780c; // G
    colorComponents[2] = _DAT_00d5780c; // B
    colorComponents[3] = _DAT_00d5780c; // A

    // Position from object (offset +0x10, +0x14, +0x18)
    colorComponents[0] = 0.0f; // not really, local_64 = 0
    colorComponents[1] = *(float *)(this + 0x10);
    colorComponents[2] = *(float *)(this + 0x14);
    colorComponents[3] = *(float *)(this + 0x18);

    // Initialize transformation matrix in buffer
    initMatrix(buffer, &colorComponents); // FUN_0044b4e0

    // --- Load mode 0: create/load primary resource ---
    if (loadMode == 0) {
        namePtr = *(undefined1 **)(this + 0x10c); // primary name string
        if (namePtr == (undefined1 *)0x0) {
            namePtr = &DAT_0120546e; // default empty string
        }
        // Build resource name: "name_ID"
        __snprintf(formattedName, 0x40, "%s_%u", namePtr, *(undefined4 *)(this + 0x38));

        filepathCombine(formattedName); // FUN_004eacb0 - possibly prepend path

        // Load resource via stream loader
        loadStreamResource(&tempHandle, &colorR, buffer, 0x2ff, 4, 0, 0xffffffff, 0); // FUN_004df420

        resourceHandle = (int *)(this + 0x180);
        if (*(int *)(this + 0x180) != 0) {
            *(undefined4 *)(*(int *)(this + 0x180) + 8) = 0;
            *resourceHandle = 0;
        }
        *resourceHandle = tempHandle;
        if (tempHandle != 0) {
            *(int **)(tempHandle + 8) = resourceHandle;
        }

        if (*resourceHandle == 0) {
            // Retry with just the name (no ID appended)
            namePtr = *(undefined1 **)(this + 0x10c);
            if (namePtr == (undefined1 *)0x0) {
                namePtr = &DAT_0120546e;
            }
            filepathCombine(namePtr);
            loadStreamResource(&tempHandle, &colorR, buffer, 0x2ff, 4, 0, 0xffffffff, 0);
            freeResourceHandle(&tempHandle); // FUN_00414db0
            if (tempHandle != 0) {
                *(undefined4 *)(tempHandle + 8) = 0;
            }
        }
        else {
            // Look up color data from some database using ID at +0x40
            lookupHandle = getColorData(*(undefined4 *)(this + 0x40)); // FUN_008c74d0
            if (lookupHandle != 0) {
                colorData = *(uint *)(lookupHandle + 0xfc);
                colorR = (float)(colorData & 0xff);
                colorG = (float)(colorData >> 8 & 0xff);
                colorB = (float)(colorData >> 16 & 0xff);
                colorA = 0.0f;
                setModelColor(&colorR); // FUN_004df760 - likely sets material tint
            }
        }
        return *resourceHandle != 0;
    }

    // --- Load mode 1: load alternative/streaming resource ---
    if (loadMode != 1) {
        return false;
    }

    // Determine which name string to use based on current state
    int state = getCurrentLoadState(); // thunk_FUN_006b4860
    if ((state == 4) || (state == 3)) {
        selectedName = *(char **)(this + 0x11c);
    }
    else if (*(int *)(this + 0xfc) == 0) {
        state = getCurrentLoadState();
        if (state != 2) {
            return false;
        }
        selectedName = *(char **)(this + 0x13c);
    }
    else {
        selectedName = *(char **)(this + 0x12c); // offset 300
    }

    if (selectedName == (char *)0x0) {
        selectedName = &DAT_0120546e;
    }
    if (*selectedName == '\0') {
        return false;
    }

    // Build filename "name_ID"
    __snprintf(formattedName, 0x40, "%s_%u", selectedName, *(undefined4 *)(this + 0x38));

    // Load using different loader (maybe async/streaming)
    int loadResult = loadResourceAsync(&tempHandle, formattedName, buffer, 0x2ff, 4, 0, 0xffffffff, 0); // FUN_0045c740
    freeResourceHandle(loadResult); // FUN_00414db0
    cleanupAfterLoad(); // FUN_00414df0

    loadSuccess = (*(int *)(this + 0x17c) == 0);
    if (loadSuccess) {
        // Retry with just the name (no ID)
        loadResult = loadResourceAsync(&tempHandle, selectedName, buffer, 0x2ff, 4, 0, 0xffffffff, 0);
        freeResourceHandle(loadResult);
        cleanupAfterLoad();
        loadSuccess = (*(int *)(this + 0x17c) == 0);
    }
    return !loadSuccess;
}