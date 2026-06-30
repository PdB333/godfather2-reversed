// FUNC_NAME: MessageHandler::dispatch
// Reconstructed from address 0x007157d0
// This function implements a two-phase message dispatch:
// Phase 1: direct virtual dispatch via message object and manager
// Phase 2: fallback using a stack-based processing frame with return-address capture

int __thiscall MessageHandler::dispatch(void *thisPtr, int *message, void *manager /* passed in EDI */) {
    // +0x0C: bit 1 controls whether this handler is active
    if ((*(unsigned int *)((char *)thisPtr + 0x0C) >> 1) & 1) {
        return 0; // Handler disabled
    }

    int directResult = 0;

    // Query the message object via virtual call at vtable+0x10 (hash 0xad29009e)
    bool canHandleDirect = (**(bool (__thiscall **)(int, int *))(*message + 0x10))(0xad29009e, &directResult);

    if (canHandleDirect && manager != 0) {
        // Ask the manager if it can accept the listener stored at this+0x10
        bool managerAccepts = (**(bool (__thiscall **)(void *))(*manager + 8))(*(void **)((char *)thisPtr + 0x10));
        if (managerAccepts) {
            return 1; // Direct dispatch succeeded
        }
    }

    // Phase 2: stack-based processing
    char stackFrame[20]; // +0x14 in local space, used as a thread/fiber stack frame
    int returnAddress;   // Captured return address of this function (passed via register/stack)

    pushStackFrame(&stackFrame, message);                 // FUN_00732460
    int state = getStackState(&stackFrame, returnAddress); // FUN_00713960

    // Fallback condition: no message or state is 1 or 2
    if (message == 0 || state == 1 || state == 2) {
        prepareMessage(message, stackFrame);                    // FUN_00712ff0
        int result = processWithStack(stackFrame, returnAddress, message, message); // FUN_00715290
        return result;
    }

    return 0;
}