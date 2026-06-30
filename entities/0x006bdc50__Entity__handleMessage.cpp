// FUNC_NAME: Entity::handleMessage

void __thiscall Entity::handleMessage(int thisPtr, int* message)
{
    // Acquire reference to message object
    acquireMessage(message);

    int messageType = *message;

    // Message type: DAT_0120e93c – initial state message
    if (messageType == DAT_0120e93c)
    {
        releaseMessage(&DAT_0120e93c);

        if (*(int*)(thisPtr + 0x34) == 0)  // currentStateId == 0
        {
            int* component = (int*)getComponentFromOffset(thisPtr + 0x24);  // componentPtr
            if (component == nullptr)
                goto cleanup;

            if (isConditionMet())
            {
                // Call vtable func at offset 0x1c (index 7) on outer object (this - 0x3c)
                (*(void (**)(int))(*(int*)component + 0x1c))(thisPtr - 0x3c);
                return;
            }
        }
    }
    // Message type: DAT_0112a6ac – secondary type
    else if (messageType == DAT_0112a6ac)
    {
        int param = getMessageParameter(message[1]);  // message[1] is data
        if (param != 0 && processSpecificMessage(param))
        {
            releaseMessage(&DAT_0112a6ac);
            return;
        }
    }
    // Message type matches currentStateId
    else if (messageType == *(int*)(thisPtr + 0x34))
    {
        if (isConditionMet())
        {
            int* component = (int*)getComponentFromOffset(thisPtr + 0x24);
            if (component == nullptr)
                goto cleanup;

            if (isConditionMet())
            {
                (*(void (**)(int))(*(int*)component + 0x1c))(thisPtr - 0x3c);
                return;
            }
        }
    }
    else
    {
        // Not matching linkedStateId
        if (messageType != *(int*)(thisPtr + 0x3c))
        {
            // Message type: DAT_012067dc – special trigger
            if (messageType == DAT_012067dc)
            {
                if (*(int*)(thisPtr + 0x94) != 0)  // someFlag
                    doPrimaryAction();
            }
        }
        doSecondaryAction();
    }
    return;

cleanup:
    someCleanup(&DAT_0112a6ac);
}