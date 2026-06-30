// FUNC_NAME: AptActionInterpreter::processAction
void __thiscall AptActionInterpreter::processAction(void* this) {
    char buffer[256]; // local_100
    int result;
    debug_assert_data debugData;
    int* moduleInfo;
    int moduleFlags;
    bool debugEnabled;
    
    result = someReadFunction(this, buffer, 0x100, 0); // FUN_005adfa0
    if (result != 0) {
        goto cleanup;
    }
    
    debugData.message = (char*)&"Assertion failed"; // DAT_00e3d06c
    debugData.file = "..\\source\\Apt\\AptActionInterpreter.cpp";
    debugData.line = (int*)0x473; // line 1139
    debugData.flags = 2;
    debugEnabled = (bool)&debugEnabled; // DAT_01128ff5 pointer to global flag
    
    // Check if debug reporting is enabled
    if (*debugEnabled == '\0') {
        goto cleanup;
    }
    
    moduleInfo = *(int**)(**(int**)(*(int*)(__readfsdword(0x2C) + 0x30)));
    moduleFlags = 1;
    if (moduleInfo != 0) {
        moduleFlags = (**(int(__thiscall**)(int*))(*(int*)moduleInfo + 8))(&debugData.message, &DAT_00e3d06c);
        if (debugEnabled != 0) {
            if ((moduleFlags & 2) != 0) {
                *debugEnabled = 0;
            }
        }
    }
    
    if ((moduleInfo != 0) || (debugData.flags != 4)) {
        if (((moduleFlags & 1) != 0) || ((debugData.flags == 0) || (debugData.flags == 1))) {
            // Trigger debug break
            __debugbreak();
            return;
        }
    }
    
cleanup:
    someCleanup1(); // FUN_005a0980
    someCleanup2(); // FUN_005a1060
    if ((debugData.line != &debugData.flags) && (debugData.line != 0)) {
        (DAT_0119caf4)(debugData.line); // likely operator delete
    }
    return;
}