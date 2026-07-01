// FUNC_NAME: GameMessageHandler::dispatchMessage
void __thiscall GameMessageHandler::dispatchMessage(uint thisPtr, int *messageData)
{
    int msgType;
    int extraData;
    int local_18;
    int local_14;
    undefined1 local_10;
    undefined4 local_c;
    int local_8;
    undefined1 local_4;

    msgType = *messageData;
    if (msgType == DAT_01206760) // kMsgTypeA
    {
        // Set timer/callback with value derived from messageData[1] offset +0x1c
        FUN_004035f0(*(undefined4 *)(*(int *)(messageData[1] + 0xc) + 0x1c), 2,
                     -(uint)(thisPtr != 0x3c) & thisPtr);

        // Release object at thisPtr+0x1c if present
        if (*(int *)(thisPtr + 0x1c) != 0)
        {
            FUN_004daf90((undefined4 *)(thisPtr + 0x1c));
            *(undefined4 *)(thisPtr + 0x1c) = 0;
        }

        // Check bit 28 of thisPtr+0x24
        if ((*(uint *)(thisPtr + 0x24) >> 0x1c & 1) == 0)
        {
            // Call virtual function at vtable[0x1c/4]? 
            // thisPtr-0x3c suggests vtable is at negative offset? Might be a handle offset.
            (**(code **)(*(int *)(thisPtr - 0x3c) + 0x1c))(0);
            return;
        }
    }
    else if (msgType == DAT_0112fddc) // kMsgTypeB
    {
        extraData = messageData[1];
        FUN_008cfdd0(extraData);
        // If thisPtr+0x1c is non-zero and not 0x48, construct a new message on stack
        if ((*(int *)(thisPtr + 0x1c) != 0) && (*(int *)(thisPtr + 0x1c) != 0x48))
        {
            local_18 = DAT_0112fddc;
            int val = *(int *)(thisPtr + 0x1c);
            local_10 = 0;
            if ((val == 0) || (val == 0x48))
            {
                val = 0;
            }
            else
            {
                val = val + -0xc;
            }
            local_14 = extraData;
            FUN_00408bf0(&local_18, val, 0); // Send new message

            val = *(int *)(thisPtr + 0x1c);
            local_c = DAT_0112fdf8; // Another message type
            local_4 = 0;
            local_8 = extraData;
            if ((val != 0) && (val != 0x48))
            {
                FUN_00408bf0(&local_c, val + -0xc, 0);
                return;
            }
            FUN_00408bf0(&local_c, 0, 0);
            return;
        }
    }
    else if (msgType == DAT_0112fde8) // kMsgTypeC
    {
        if ((*(int *)(thisPtr + 0x1c) != 0) && (*(int *)(thisPtr + 0x1c) != 0x48))
        {
            int val2 = *(int *)(thisPtr + 0x1c);
            if ((val2 == 0) || (val2 == 0x48))
            {
                val2 = 0;
            }
            else
            {
                val2 = val2 + -0xc;
            }
            FUN_00408b80(&DAT_0112fde8, val2, 0); // Another send mechanism
            // Check bit 29 of thisPtr+0x24
            if ((*(uint *)(thisPtr + 0x24) >> 0x1d & 1) == 0)
            {
                FUN_004088c0(thisPtr);
                return;
            }
        }
    }
    else if (msgType == DAT_0120e93c) // kMsgTypeD
    {
        FUN_004086d0(&DAT_0120e93c); // Clear/handle this message type
    }
    return;
}