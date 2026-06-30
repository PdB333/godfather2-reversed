// FUNC_NAME: MessageHandler::processMessage
undefined4 __thiscall MessageHandler::processMessage(int this, undefined4 *message)
{
    int iVar1;
    undefined4 result;
    char flag;
    int local_20;
    char local_1c;
    undefined4 local_18;
    int local_14;
    undefined4 local_10;
    undefined4 local_c;

    local_20 = this; // unused

    // Check if message type matches first accepted type
    if (message[2] == *(int *)(this + 0x18)) {
        result = processType1Message(); // FUN_00616bc0
        return result;
    }

    // Check if message type matches second accepted type
    if (message[2] == *(int *)(this + 0x1c)) {
        // Get some value from message data
        result = resolveObject(*(undefined4 *)(message[1] + 0xc)); // FUN_00611000
        flag = '\0';
        // Check condition on message field [5]
        checkCondition(message[5], &flag); // FUN_0061a2e0
        if (flag != '\0') {
            iVar1 = message[5];
            local_1c = 0;
            if (iVar1 != 0) {
                local_10 = message[4];
                message[5] = 0;
                message[4] = 0;
                message[7] = 0;
                local_14 = iVar1;
            }
            local_c = message[6];
            local_18 = result;
            processType2Data(); // FUN_0061a6b0
        }
        // Increment message reference count
        *(int *)*message = *(int *)*message + 1;
        return result;
    }

    return 0;
}