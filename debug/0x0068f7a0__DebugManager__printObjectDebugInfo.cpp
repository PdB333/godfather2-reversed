// FUNC_NAME: DebugManager::printObjectDebugInfo
void __thiscall DebugManager::printObjectDebugInfo(int objectId, char verbose, char* outputBuffer) {
    // Global DebugManager singleton pointer (DAT_012233b4)
    DebugManager* self = *(DebugManager**)0x012233b4;

    // Initialize debug context structure on stack
    struct DebugContext {
        void** vtable;          // +0x00: pointer to vtable for this context
        int resultCode;         // +0x04: result from iteration (0 = continue, 4 = skip)
        int threshold;          // +0x08: filter threshold (initialized to 7 or 3 based on global flag)
        int objectId;           // +0x0C: the object ID to debug
        char hasOutput;         // +0x10: flag set by visitor if output exists
        int unknown1;           // +0x14: initially -1
        int stringBuffer;       // +0x18: initially 0 (pointer to allocated string)
        int pad;                // +0x1C: uninitialized
        int pad2;               // +0x20: uninitialized
        void (*cleanupFunc)(int); // +0x24: function pointer for cleanup
    };

    DebugContext ctx;
    // Set vtable to a predefined function table (PTR_FUN_00d5c878)
    ctx.vtable = &PTR_FUN_00d5c878;
    ctx.resultCode = 0;
    // Determine threshold: if a specific global flag is set (0x12), use 3; else 7
    ctx.threshold = (*(char*)((char*)self + 0x568) == '\x12') ? 3 : 7;
    ctx.objectId = objectId;
    ctx.hasOutput = '\0';
    ctx.unknown1 = -1;
    ctx.stringBuffer = 0;
    ctx.cleanupFunc = nullptr;

    // Start iteration over all registered debug objects
    debugIterBegin(); // Likely FUN_00495960
    while (debugIterHasNext()) { // Likely FUN_00495980
        void* currentObject = debugIterNext(); // Likely FUN_004959c0
        int** vtable = *(int***)currentObject;
        // Call the virtual method at offset 0x14 (5th method) on the object,
        // passing the debug context (by pointer). This method typically populates the context.
        typedef void (*VisitorMethod)(DebugContext*);
        ((VisitorMethod)(*vtable[0x14 / 4]))(&ctx);
    }

    if (ctx.resultCode != 4) {
        // Try to find a specific debug object for the given ID
        int* debugObj = findDebugObject(objectId); // Likely FUN_0068f680
        if (debugObj == nullptr || *(int**)(debugObj + 2) == nullptr) {
            // No object found, output the accumulated string if any
            if (ctx.hasOutput != '\0') {
                if (verbose != '\0') {
                    enableConsoleOutput(); // Likely FUN_00401060
                }
                // Release previous buffer if any? (FUN_004d3b50 on &ctx.stringBuffer)
                freeStringBuffer(&ctx.stringBuffer);
                // There's additional buffer management using puStack_40 and iStack_3c
                // These are actually fields from the DebugContext after the strings?
                // They are referenced as separate stack variables due to Ghidra's analysis.
                // We'll assume they are part of the context's internal string handling.
                int* extraPtr = (int*)((char*)&ctx + 0x28); // approximate offset
                if (extraPtr[0] != 0) {
                    // Perform some cleanup on extra pointer
                    ((void (*)(int*))extraPtr[2])((int*)extraPtr[0]); // call cleanup
                }
                // Additional buffer: if a second pointer exists, print it
                int secondaryBuffer = *(int*)((char*)&ctx + 0x2C); // iStack_3c
                if (secondaryBuffer != 0) {
                    freeStringBuffer(&ctx.stringBuffer);
                    const char* str = (const char*)(extraPtr[0] ? extraPtr[0] : &DAT_0120546e);
                    // Format and append the string to output
                    formatPrint(outputBuffer, "[c=CUSTOM1]%s[c=RESET] ", str);
                    if (extraPtr[0] != 0) {
                        ((void (*)(int*))extraPtr[2])((int*)extraPtr[0]);
                    }
                }
            }
        } else {
            // Object found directly – print its name
            if (verbose != '\0') {
                enableConsoleOutput();
            }
            printObjectName(*(int*)(debugObj + 2)); // Likely FUN_004d4300
        }
    }

    // Free the string buffer if allocated
    if (ctx.stringBuffer != 0) {
        ctx.cleanupFunc(ctx.stringBuffer);
    }
}