// FUNC_NAME: StreamLoader::processLoad
void __thiscall StreamLoader::processLoad(int param_1, int param_2) {
    char cVar1;
    int iVar2;
    char *pcVar3;
    undefined4 uVar4;
    undefined4 uVar5;
    char local_90c[4];
    undefined1 local_908[256];
    char local_808[1024];
    char local_408[1028];

    // Check if loading is allowed globally
    cVar1 = isLoadAllowed();
    if (cVar1 == '\0') {
        // Only proceed if we are in state 2 (in progress)
        if (*(int *)(param_1 + 0xc) != 2) {
            return;
        }
        // Begin async load with given parameter
        beginAsyncLoad(param_2);

        // Read "CDBL" (compressed data block?) into dataBuffer
        readResourceData(*(undefined4 *)(param_1 + 4), 0x6364626c, 0, local_408);

        // Get resource path string
        iVar2 = getResourcePath(*(undefined4 *)(param_1 + 4), local_908);

        // If path retrieved and resource has positive size
        if ((iVar2 == 0) && (iVar2 = getResourceSize(*(undefined4 *)(param_1 + 4)), 0 < iVar2)) {
            // Transistion to state 3 (processing)
            *(undefined4 *)(param_1 + 0xc) = 3;

            // Read 4-byte "LCOL" (local offset?) token
            readResourceProperty(*(undefined4 *)(param_1 + 4), 0x6c6f636c, local_90c, 4);

            // Search for that token in the data buffer
            pcVar3 = _strstr(local_408, local_90c);
            if (pcVar3 == (char *)0x0) {
                // Not found in first buffer, try second (uninitialized – bug or placeholder)
                pcVar3 = _strstr(local_808, local_90c);
                if (pcVar3 == (char *)0x0) {
                    // Not found in either: set halt flag to 1, state to 4
                    uVar4 = *(undefined4 *)(param_1 + 4);
                    uVar5 = 1;
                    *(undefined4 *)(param_1 + 0xc) = 4;
                } else {
                    // Found in second buffer: set halt to 0
                    uVar4 = *(undefined4 *)(param_1 + 4);
                    uVar5 = 0;
                }
            } else {
                // Found in first buffer: set halt to 1
                uVar4 = *(undefined4 *)(param_1 + 4);
                uVar5 = 1;
            }
            // Store the halt decision (4CC "HALT")
            setResourceProperty(uVar4, 0x68616c74, uVar5, 0);

            // Invoke global callback with user data at offset +8
            if (g_loadCallback != (code *)0x0) {
                (*g_loadCallback)(*(undefined4 *)(param_1 + 8));
            }
            return;
        }
    }
    // On error or loading disallowed, set state to 5 (error/stop)
    *(undefined4 *)(param_1 + 0xc) = 5;
    return;
}