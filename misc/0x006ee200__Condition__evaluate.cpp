// FUNC_NAME: Condition::evaluate
bool Condition::evaluate(int* condition, int context)
{
    int type = condition[0];
    if (type == 0)
    {
        // Boolean type condition
        char result1 = evaluateBoolCondition(condition[1], condition[2], context);
        char result2 = evaluateBoolCondition(condition[3], condition[4], context);
        return (result1 != '\0') || (result2 != '\0');
    }
    else if (type == 1)
    {
        // Integer type condition
        int result1 = evaluateIntCondition(condition[1], condition[2], context);
        int result2 = evaluateIntCondition(condition[3], condition[4], context);
        return (result1 != 0) || (result2 != 0);
    }
    else if (type == 2)
    {
        // Float type condition
        float result1 = evaluateFloatCondition(condition[1], condition[2], context);
        float result2 = evaluateFloatCondition(condition[3], condition[4], context);
        // _DAT_00d577a0 is a global float constant 0.0f
        return (result1 != 0.0f) || (result2 != 0.0f);
    }
    return false;
}