// FUNC_NAME: ConditionEvaluator::evaluateCondition
// Address: 0x006ecf70
// Role: Evaluates a typed condition against a context value (param_2). The condition data is stored in an array of ints:
//   [0] = type (0: char, 1: int, 2: float)
//   [1] = left operand
//   [2] = right operand (used in comparisons)
//   [3] = expected result (for exact equality check)
// Returns true if condition passes, false otherwise.

bool evaluateCondition(int* conditionData, int contextValue)
{
    int type = conditionData[0];          // +0x00: condition type
    bool result = false;

    if (type == 0) // char comparison
    {
        char comparisonResult = compareCharValues(conditionData[1], conditionData[2], contextValue);
        result = (comparisonResult == (char)conditionData[3]);
    }
    else if (type == 1) // int comparison
    {
        int comparisonResult = compareIntValues(conditionData[1], conditionData[2], contextValue);
        return (comparisonResult == conditionData[3]);
    }
    else if (type == 2) // float comparison
    {
        float comparisonResult = compareFloatValues(conditionData[1], conditionData[2], contextValue);
        if (comparisonResult == (float)conditionData[3])
            return true;
        return false;
    }

    return result;
}