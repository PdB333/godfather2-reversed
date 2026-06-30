// FUNC_NAME: NetSession::dispatchMessage
void __thiscall NetSession::dispatchMessage(int thisPtr, int messageNode, int messageData, int context1, int context2) {
    int msgId;
    // Temporary stack structure for message dispatch
    struct DispatchContext {
        undefined4 field_0; // +0x00
        undefined4 *handlerTablePtr; // +0x04
        undefined field_8; // +0x08
        undefined4 field_C; // +0x0C
        int listHead; // +0x10
        int savedNext; // +0x14
        undefined4 field_18; // +0x18
        undefined4 field_1C; // +0x1C
        undefined4 field_20; // +0x20 (context1)
    };

    int localStackHead = 0;
    int savedNext = 0;
    DispatchContext ctx;
    undefined4 global1 = DAT_01205228; // Global pointer
    undefined4 global2 = DAT_0112ad8c; // Another global

    msgId = extractMessageId(messageData); // FUN_006b0f50, likely returns message type

    // First case: message ID matches our stored ID at +0x1ed4
    if (msgId == *(int *)(thisPtr + 0x1ed4)) {
        // Initialize dispatch context
        ctx.field_0 = 0;
        ctx.field_C = 0;
        ctx.field_1C = 0;
        ctx.handlerTablePtr = &PTR_FUN_00d5dbbc; // Static function pointer table
        ctx.listHead = 0;
        ctx.savedNext = 0;
        ctx.field_8 = 0;
        ctx.field_18 = global1;
        ctx.field_20 = context1; // First extra parameter

        // If messageNode is valid and its +0x48 field is non-zero, manipulate linked list
        if (messageNode != 0 && (messageNode + 0x48) != 0) {
            savedNext = *(int *)(messageNode + 0x4c); // Save original next pointer
            *(int **)(messageNode + 0x4c) = &localStackHead; // Point next to our stack head
            localStackHead = messageNode + 0x48; // Set stack head to point to node's +0x48 field
        }

        ctx.savedNext = savedNext; // Copy saved next into context? Actually this is overwritten below.
        ctx.handlerTablePtr = &ctx.handlerTablePtr; // Not sure why, but original does &local_24
        invokeMessageHandler(&global2, thisPtr + 0x3c, 0); // FUN_00408bf0, processes message

        if (localStackHead != 0) {
            cleanupTemporaryList(&localStackHead); // FUN_004daf90, likely frees temporary list
        }
    }
    // Second case: message ID matches messageNode's ID at +0x1ed4
    else if (msgId == *(int *)(messageNode + 0x1ed4)) {
        ctx.field_20 = context2; // Use second context this time
        ctx.field_0 = 0;
        ctx.field_C = 0;
        ctx.field_1C = 0;
        ctx.handlerTablePtr = &PTR_FUN_00d5dbbc;
        ctx.listHead = 0;
        ctx.savedNext = 0;
        ctx.field_8 = 0;
        ctx.field_18 = global1;

        if ((messageNode + 0x48) != 0) {
            savedNext = *(int *)(messageNode + 0x4c);
            *(int **)(messageNode + 0x4c) = &localStackHead;
            localStackHead = messageNode + 0x48;
        }

        ctx.savedNext = savedNext;
        ctx.handlerTablePtr = &ctx.handlerTablePtr;
        invokeMessageHandler(&global2, thisPtr + 0x3c, 0);

        if (localStackHead != 0) {
            cleanupTemporaryList(&localStackHead);
        }
    }
    return;
}