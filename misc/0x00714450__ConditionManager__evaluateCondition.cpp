// FUNC_NAME: ConditionManager::evaluateCondition

int __thiscall ConditionManager::evaluateCondition(ConditionManager* this, int conditionId, float mode)
{
    int index;
    float* conditionData;

    if (conditionId == 0) {
        return 0;
    }

    index = getCurrentConditionIndex(); // FUN_0077dd80
    conditionData = getConditionData(conditionId); // FUN_00713c10
    if (conditionData == nullptr) {
        return 0;
    }

    conditionData[1] = mode; // store the mode
    float difference = g_globalBase - conditionData[0]; // DAT_01205228 - stored value

    bool isLessOrEqual;
    float threshold;

    // The special float values are very small subnormals, used as mode identifiers
    if (mode == 1.4013e-45f) { // mode 0
        threshold = g_constantThreshold0; // _DAT_00d577a0
        isLessOrEqual = (difference < threshold) || (difference == threshold);
    }
    else if (mode == 2.8026e-45f) { // mode 1
        threshold = *(float*)((uint8_t*)this + 0x7c + index * 4); // threshold array at +0x7c
        isLessOrEqual = (difference < threshold) || (difference == threshold);
    }
    else if (mode == 4.2039e-45f) { // mode 2
        threshold = *(float*)((uint8_t*)this + 0x9c + index * 4); // threshold array at +0x9c
        isLessOrEqual = (difference < threshold) || (difference == threshold);
    }
    else {
        // Only the three specific modes are valid; return false otherwise
        return 0;
    }

    // Return true if difference is strictly greater than the threshold
    return (isLessOrEqual) ? 0 : 1;
}