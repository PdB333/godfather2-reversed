// FUNC_NAME: ActionHandler::handleActionEvent
int __fastcall ActionHandler::handleActionEvent(int thisPtr)
{
    int *actionArray;
    int actionState;
    int somePtr;
    int local4;
    char result;

    // +0x28: index into global action data array
    int index = *(int*)(thisPtr + 0x28);
    if (index != -1)
    {
        // Base global DAT_0112a9f4, array of structs (size 0x58) starting at offset 0x78
        actionArray = (int*)(DAT_0112a9f4 + 0x78 + index * 0x58);
        if (actionArray != nullptr)
        {
            actionState = actionArray[0];   // state field (1 or 6 active)
            local4 = thisPtr;               // saved for later use
            if (actionState == 1 || actionState == 6)
            {
                // +8 fields: actionArray[2] is an action pointer/flag
                if (actionArray[2] != 0)
                {
                    if (actionState == 6)
                    {
                        FUN_006fbd30();     // cancel action callback (state 6)
                    }
                    else // state == 1
                    {
                        actionArray[0] = 0; // reset state
                        actionArray[1] = 0; // clear secondary field
                    }
                }
            }
            else
            {
                // +0x10: pointer to a sub-object (possibly component)
                int subObj = *(int*)(thisPtr + 0x10);
                if (subObj != 0 && subObj != 0x48)
                {
                    int adjusted;
                    if (subObj == 0)
                        adjusted = 0;
                    else
                        adjusted = subObj - 0x48; // subtract offset to get base of parent object

                    // +0x2c: flags, bit1 indicates a condition
                    bool flag = (*(byte*)(thisPtr + 0x2c) & 2) != 0;
                    result = FUN_006fc960(adjusted, flag);
                    if (result)
                        return 1;
                }
            }
        }
    }

    // Second check on sub-object pointer
    int subObj2 = *(int*)(thisPtr + 0x10);
    if (subObj2 != 0 && subObj2 != 0x48)
    {
        int* baseObj;
        if (subObj2 == 0)
            baseObj = nullptr;
        else
            baseObj = (int*)(subObj2 - 0x48);   // base of parent object via embedded offset

        local4 = 0;
        // Call virtual function at vtable+0x10 on the parent object
        // First arg is a magic constant (event/hash), second is output int
        bool (__stdcall *vfunc)(int, int*) = (bool (__stdcall*)(int, int*))(*(int*)(*baseObj + 0x10));
        result = vfunc(0x55859efa, &local4);
        // unaff_ESI is a preserved register (likely global state)
        if (result && unaff_ESI != 0)
        {
            FUN_007f5860(5);            // log/action call
            *(byte*)(thisPtr + 0x34) = 1;  // set success flag
            return 1;
        }
    }
    return 0;
}