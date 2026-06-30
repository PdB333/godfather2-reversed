// FUNC_NAME: evaluateConditionNode
int evaluateConditionNode(int conditionBlock[5], int context)
{
    int mode = conditionBlock[0];
    if (mode == 0) {
        // char bool case
        bool cond1 = evaluateConditionChar(conditionBlock[1], conditionBlock[2], context);
        bool cond2 = evaluateConditionChar(conditionBlock[3], conditionBlock[4], context);
        if (cond1 && cond2) {
            return 0;
        }
    } else if (mode == 1) {
        // int bool case
        int cond1 = evaluateConditionInt(conditionBlock[1], conditionBlock[2], context);
        int cond2 = evaluateConditionInt(conditionBlock[3], conditionBlock[4], context);
        if (cond1 != 0) {
            if (cond2 != 0) {
                return 0;
            }
            return 1;
        }
    } else if (mode == 2) {
        // float comparison case
        float cond1 = evaluateConditionFloat(conditionBlock[1], conditionBlock[2], context);
        float cond2 = evaluateConditionFloat(conditionBlock[3], conditionBlock[4], context);
        // _DAT_00d577a0 is a special global float (e.g., NaN or sentinel)
        if ((cond1 != 0.0f) && (cond2 != _DAT_00d577a0)) {
            return 0;
        }
    } else {
        return 0;
    }
    return 1;
}