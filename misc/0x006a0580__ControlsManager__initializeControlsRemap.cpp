// FUNC_NAME: ControlsManager::initializeControlsRemap
void ControlsManager::initializeControlsRemap(void) {
    wchar_t *controlsRmpPath; // puVar1
    int result; // iVar2
    wchar_t *pathBuf; // puVar3
    wchar_t **ppPathBuf; // ppuVar4
    int unaff_EDI; // unaff_EDI
    wchar_t *stackPathBuf; // puStack_260
    wchar_t *local_248; // local_248
    wchar_t *local_218[4]; // local_218
    wchar_t buffer[520]; // local_208

    controlsRmpPath = (wchar_t *)PTR_u_controls_rmp_00e50c74; // "controls_rmp" wide string
    if (*(int *)(g_GameModule + 0x2264) == 0) {
        errorHandler(); // FUN_006a0430
        return;
    }

    // Copy base path from global
    getStringBasePath(); // FUN_004dbef0
    // Concat with controlsRmpPath
    stringConcat(controlsRmpPath); // FUN_004dba00

    // Get another path from global
    wchar_t *basePath2 = *(wchar_t **)(g_GameModule + 0x2264);
    // Concat with basePath2
    stringConcat(basePath2); // FUN_004dba00

    if (local_248 == nullptr) {
        local_248 = &emptyWideString; // &DAT_00e2df14 (empty string?)
    }

    // Get final path string (maybe resolve "controls_rmp" to full path)
    local_218[0] = createPathString(local_248); // FUN_00699080
    if (local_218[0] == nullptr) {
        local_218[0] = &emptyWideString;
    }

    // Use SHGetFolderPathAndSubDirW to get actual user folder path
    // 0x8005 = CSIDL_PERSONAL (My Documents)
    stackPathBuf = (wchar_t *)0x8005; // CSIDL flag
    result = SHGetFolderPathAndSubDirW(nullptr, stackPathBuf, nullptr, SHGFP_TYPE_CURRENT, local_218[0]);
    if (result == 0) {
        // Success: build full file path
        buildFilePath(&emptyWideString, 1, iStack_240, uStack_23c); // FUN_004dbf70
        copyString(buffer, 0, unaff_EDI); // FUN_004dbd90
        if (buffer != nullptr) {
            freeString(buffer); // pcStack_244 is likely free function
        }

        pathBuf = stackPathBuf;
        if (stackPathBuf == nullptr) {
            pathBuf = &emptyWideString;
        }
        // Build final path with subfolder and file
        ppPathBuf = buildPath(&stack0xfffffdb0, pathBuf, 3); // FUN_00699080
        if (&stackPathBuf != ppPathBuf) {
            pathBuf = *ppPathBuf;
            if (pathBuf == nullptr) {
                pathBuf = &emptyWideString;
            }
            stringCopy(pathBuf, 0, ppPathBuf[1]); // FUN_004dbb10
        }
        if (buffer != nullptr) {
            freeString(buffer);
        }
        pathBuf = stackPathBuf;
        if (stackPathBuf == nullptr) {
            pathBuf = &emptyWideString;
        }
        readFile(pathBuf); // FUN_00497620
    } else {
        errorHandler(); // FUN_006a0430
    }

    // Cleanup
    if (iStack_230 != 0) {
        freeMemory(iStack_230);
    }
    if (stackPathBuf != nullptr) {
        freeString(stackPathBuf);
    }
    if (iStack_240 != 0) {
        freeMemory(iStack_240);
    }
}