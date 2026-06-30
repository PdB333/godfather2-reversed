// FUNC_NAME: PlayerInputHandler::processEvent
void __thiscall PlayerInputHandler::processEvent(int *eventStruct, uint param_1)
{
    // eventStruct[0] is event type, eventStruct[1] is data (e.g., action index)
    // this structure:
    // +0x0c : pointer to an array of ints (action look-up table)
    // +0x18 (offset 24) : counter A (decremented on specific action)
    // +0x24 (offset 36) : counter B (decremented on another action)
    // +0x34 (offset 52) : upper bound for index range check (inclusive lower bound)

    int *actionArray; // fetched from this+0x0c
    uint extractedParam;
    int actionValue;

    if (*eventStruct == 10) // action type 10: specific action with bitfield check
    {
        actionArray = *(int **)((char *)this + 0xc);
        actionValue = actionArray[eventStruct[1]]; // look up the entry for this index
        if (((byte)actionValue & 0x3f) == 0x12) // check lower 6 bits == 18 (specific action ID)
        {
            ((int *)this)[6] = ((int *)this)[6] - 1; // decrement counter A
            param_1 = (uint)(param_1 == 0); // invert the boolean flag
            extractedParam = (actionValue >> 0xf) & 0x1ff; // extract bits 15-23 (9-bit value)
        }
        else
        {
            extractedParam = eventStruct[1]; // fallback to the original index
        }
    }
    else
    {
        FUN_00642d40(); // general processing function
        if ((*eventStruct == 0xb) && // action type 11
            (((int *)this)[13] <= (uint)eventStruct[1] && eventStruct[1] < 0xfa)) // check index range
        {
            ((int *)this)[9] = ((int *)this)[9] - 1; // decrement counter B
        }
        extractedParam = eventStruct[1]; // use the index as the parameter
    }

    FUN_006424f0(0x18, extractedParam, param_1); // call event dispatcher with type 0x18
}