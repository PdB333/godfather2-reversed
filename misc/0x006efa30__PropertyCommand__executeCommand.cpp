// FUNC_NAME: PropertyCommand::executeCommand

// Address: 0x006efa30
// Dispatches a property command based on type (0=string, 1=int, 2=float).
// param_1 points to a struct with: commandType (int), destIndex1, destIndex2, srcIndex1, srcIndex2.
// param_2 is a context (e.g., UI element or renderer) passed to the helpers.

void executePropertyCommand(int* cmdParams, void* context)
{
    int cmdType = cmdParams[0];          // +0x00: command type
    int dest1 = cmdParams[1];            // +0x04: destination index 1
    int dest2 = cmdParams[2];            // +0x08: destination index 2
    int src1 = cmdParams[3];             // +0x0C: source index 1
    int src2 = cmdParams[4];             // +0x10: source index 2

    switch (cmdType)
    {
    case 0: // string property
    {
        char* strValue = getStringValue(src1, src2, context);
        setStringValue(dest1, dest2, context, strValue);
        break;
    }
    case 1: // int property
    {
        int intValue = getIntValue(src1, src2, context);
        setIntValue(dest1, dest2, context, intValue);
        break;
    }
    case 2: // float property
    {
        double dblValue = getDoubleValue(src1, src2, context);
        float floatValue = (float)dblValue;
        setFloatValue(dest1, dest2, context, floatValue);
        break;
    }
    }
    return;
}