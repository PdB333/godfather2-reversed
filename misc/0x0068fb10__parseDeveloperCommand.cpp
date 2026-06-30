// FUNC_NAME: parseDeveloperCommand

// Function address: 0x0068fb10
// Parses a developer command string, executes matching callbacks.
// Checks global debug mode flag (offset 0x568 of DAT_012233b4) or enables via FUN_0068e8f0(4).
// Iterates through tokens, hashes each token, and registers callback for matched commands.
// Calls final callback if any.

struct CallbackContext {
    int count;              // +0x00
    int capacity;           // +0x04
    int unknown;            // +0x08
    void (*callback)(int);  // +0x0C
};

void parseDeveloperCommand(char** inputStringPtr) {
    char cVar1;
    int iVar2;
    char* tokenPtr;
    char* cmdString;
    int length1;
    int length2;
    int idx;
    int callbackID;
    char* tokenStart;
    char* basePtr;
    int tokenLen;
    char* scanPtr;
    int scanLen;
    CallbackContext ctx;
    int local_14;

    // Check if debug mode is active (global byte at 0x568 of base == 0x12) or if we can enable it (function returns non-zero)
    if ((*(char*)(DAT_012233b4 + 0x568) == 0x12) || (cVar1 = FUN_0068e8f0(4), cVar1 == '\0')) {
        cmdString = *inputStringPtr;
        if (cmdString == (char*)0x0) {
            cmdString = &DAT_0120546e; // default empty string
        }

        // Compute length
        idx = 0;
        tokenPtr = cmdString;
        while (*tokenPtr != '\0') {
            tokenPtr++;
        }
        length1 = (int)(tokenPtr - (cmdString + 1));
        tokenPtr = cmdString;
        while (*tokenPtr != '\0') {
            tokenPtr++;
        }
        length2 = (int)(tokenPtr - (cmdString + 1));

        // Initialize callback context
        ctx.count = 0;
        ctx.capacity = 0;
        ctx.unknown = 0;
        ctx.callback = (void (*)(int))0x0;

        tokenStart = cmdString;
        basePtr = cmdString;
        tokenLen = length1;
        scanPtr = cmdString;
        scanLen = length2;

        cVar1 = FUN_0068e210(); // hasMoreTokens?
        while (cVar1 != '\0') {
            FUN_004d43f0(scanPtr, 0, scanLen); // advance token?
            iVar2 = FUN_004db060(basePtr + idx, basePtr + tokenLen + idx); // hash current token
            if (iVar2 == 0x12496f4c) {
                callbackID = 0x3ddc7637;
                FUN_0068f7a0(callbackID, 0, &ctx);
            } else if (iVar2 == 0x3fdf44d2) {
                callbackID = 0x2938c6cc;
                FUN_0068f7a0(callbackID, 0, &ctx);
            }
            cVar1 = FUN_0068e210();
        }

        FUN_004d3e20(&ctx); // finalize callbacks
        if (ctx.count != 0) {
            (*ctx.callback)(ctx.count);
        }
    }
}