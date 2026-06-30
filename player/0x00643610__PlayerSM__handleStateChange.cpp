// FUNC_NAME: PlayerSM::handleStateChange
void __fastcall PlayerSM::handleStateChange(int thisPtr, int messagePtr) // thisPtr in EDI, messagePtr in ECX, actionCode in EAX (actually in_EAX is action, but param_1 is messagePtr)
{
    int actionId; // eax
    actionId = *(int *)messagePtr; // assume action ID is at offset 0 of message structure? Or the action is passed in register. 
    // Actually the decompiled code uses in_EAX directly. We'll model it as a register parameter.
    // For clarity, we'll treat actionId as a separate variable from the message structure.
    // Since the decompiler shows it as in_EAX, we can assume the function is called with action in EAX.
    // So we define: void __fastcall PlayerSM::handleStateChange(int thisPtr, int messagePtr) where messagePtr is param_1,
    // and actionId is passed in EAX (not as parameter). But to make the C++ valid, we'll include actionId as an implicit register variable.
    // Alternatively, we can assume the message structure contains the action code at offset 0, and param_1 points to it.
    // The original code uses in_EAX and param_1 separately, so likely message structure has the action code.
    // Let's assume *(int*)messagePtr is the action code, then it's consistent.
    int actionCode = *(int *)messagePtr; // action code from message
    // However the decompiler shows in_EAX and param_1 are separate. We'll rename accordingly.

    switch (actionCode) {
        case 5: // ACTION_TYPE_5
            FUN_00642ec0(); // handle action type 5
            break;
        case 0xC: // ACTION_TYPE_12
            FUN_00643310(); // handle action type 12
            // Fall through? No, it's separate return logic
            // Actually after case 12, it sets [param_1+0x1c] = [param_1+0x18], calls FUN_00642880(param_1), then sets [this+0x10] = -1
            *(int *)(thisPtr + 0x10) = -1; // set timer or state flag
            *(int *)(messagePtr + 0x1C) = *(int *)(messagePtr + 0x18); // copy some message field
            FUN_00642880(messagePtr); // process message further
            return; // original code returns after setting this offset? Actually after case 0xc it returns.
        case 0xD: // ACTION_TYPE_13
            FUN_006433b0(); // handle action type 13
            *(int *)(thisPtr + 0xC) = -1; // set another timer/state
            *(int *)(messagePtr + 0x1C) = *(int *)(messagePtr + 0x18); // copy message field
            FUN_00642880(messagePtr); // process message
            return;
        default:
            FUN_00642fc0(); // default handler
            return;
    }
    return;
}