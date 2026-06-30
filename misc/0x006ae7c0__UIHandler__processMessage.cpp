// FUNC_NAME: UIHandler::processMessage
void __thiscall UIHandler::processMessage(UIHandler* this, int* messageInfo)
{
    int messageId = *messageInfo;
    int* messageData = messageInfo; // messageData[1] used for additional param

    // Initialization message (global constant)
    if (messageId == *g_MSG_INIT) // DAT_0120e93c
    {
        FUN_004086d0(&g_MSG_INIT);
        int objectHandle = *(int *)(this + 0x148);
        int* uiObj = FUN_006b0ee0(objectHandle);
        *(int **)(this + 0x144) = uiObj;

        // Adjust to base class offset (-0x3C)
        int* baseThis = (int*)((char*)this - 0x3C);
        FUN_006b5b80(baseThis);
        FUN_006b1560(baseThis);

        int context = FUN_006b4860(); // e.g., getCurrentContextId
        FUN_006ae040(context);

        FUN_008f6f50(0x14, baseThis); // register for update every 20 frames?

        // Build message struct on stack for broadcast
        undefined4* local_14 = &PTR_LAB_00d5dbb0; // message type table?
        undefined4* local_c = DAT_0112a628;         // global pointer
        undefined4* local_8 = &local_14;
        undefined4 local_4 = 0;
        FUN_00408a00(&local_c, 0); // initialize message
        FUN_0046efc0(messageInfo); // dispatch to next handler
        return;
    }

    // Message IDs stored in object at various offsets
    if (messageId == *(int *)(this + 0x208))
    {
        FUN_006b2600(0); // e.g., set bool option 0
        FUN_0046efc0(messageInfo);
        return;
    }
    if (messageId == *(int *)(this + 0x210))
    {
        FUN_006b2600(1);
        FUN_0046efc0(messageInfo);
        return;
    }
    if (messageId == *(int *)(this + 0x200))
    {
        FUN_006b68c0(0x637b907, 0, 0, 0); // play sound/effect by hash
        FUN_0046efc0(messageInfo);
        return;
    }
    if (messageId == *(int *)(this + 0x220))
    {
        FUN_006b2c20(); // toggle something
        FUN_0046efc0(messageInfo);
        return;
    }
    if (messageId == *(int *)(this + 0x270))
    {
        FUN_006b6680(0x637b907, 0, 0, 0); // stop sound/effect by hash
        FUN_0046efc0(messageInfo);
        return;
    }

    // Global message ID for UI action
    if (messageId == *g_MSG_UI_ACTION) // DAT_0112a600
    {
        int paramValue = messageInfo[1]; // extra data from message
        FUN_006ae040(*(int *)(paramValue + 0xC)); // update UI based on parameter
        FUN_0046efc0(messageInfo);
        return;
    }

    // Toggle visibility flag (bit 22)
    if (messageId == *(int *)(this + 0x250))
    {
        uint* flags = (uint*)(*(int *)(this + 0x144) + 0x34); // UI object flags
        *flags |= 0x400000; // set bit 22
        undefined4* local_8 = *(undefined4***)(this + 0x144); // get UI object pointer
        undefined4 local_4 = 0;
        // Build message structure with type table
        undefined4* local_c = &PTR_LAB_00d5dbb8;
        FUN_0045c400(&DAT_0112a5c4, &local_c, 0); // broadcast toggle on message
    }
    else if (messageId == *(int *)(this + 600)) // offset 0x258
    {
        uint* flags = (uint*)(*(int *)(this + 0x144) + 0x34);
        *flags &= 0xFFBFFFFF; // clear bit 22
        undefined4* local_8 = *(undefined4***)(this + 0x144);
        undefined4 local_4 = 1;
        undefined4* local_c = &PTR_LAB_00d5dbb8;
        FUN_0045c400(&DAT_0112a5c4, &local_c, 0); // broadcast toggle off
    }

    FUN_0046efc0(messageInfo); // default dispatch
    return;
}