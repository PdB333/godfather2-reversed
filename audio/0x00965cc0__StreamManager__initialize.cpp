// FUNC_NAME: StreamManager::initialize
void StreamManager::initialize(void* param_1) {
    // Profiling/debug scope start
    FUN_00604be0(); // profilingBegin or timerStart
    FUN_00604c10(0x6b, param_1); // debugLog with level 0x6b and message/category

    // Format a unique identifier string (e.g., "{#%u}" with hash 0x2f0e7a3)
    char buffer[4112]; // large stack buffer for formatted output
    char* outStr = nullptr;
    int stringSize = 0;
    void* (*freeFunc)(char*) = nullptr;

    FUN_006038a0(DAT_012234a4, buffer, &outStr, "{#%u}", 0x2f0e7a3);
    // DAT_012234a4 likely points to an allocator context
    // outStr receives a heap-allocated string or points to static buffer

    void* obj = FUN_009c8e50(0xf0); // operatorNew(240)
    if (obj == nullptr) {
        obj = nullptr; // redundant, clarifies intent
    } else {
        obj = FUN_00982280(0); // construct the object with param 0
    }

    char* finalStr = outStr;
    if (outStr == nullptr) {
        finalStr = &DAT_0120546e; // fallback empty string
    }

    FUN_00981eb0(finalStr); // set name/path on object (e.g., setFileName)

    *(int*)((char*)obj + 0x0c) = 6; // +0x0c: type ID or state
    *(void**)((char*)obj + 0x14) = FUN_00963150; // +0x14: callback/update function pointer

    FUN_00982e10(); // startup or process registration

    FUN_00604c00(); // profilingEnd

    if (outStr != nullptr) {
        freeFunc(outStr); // free allocated string
    }
    return;
}