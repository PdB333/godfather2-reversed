// FUNC_NAME: ProcessValueWithSignAdjustment
void ProcessValueWithSignAdjustment(int index, int value) // index from param_1, value from EAX
{
    char idx = (char)index;
    bool isNegative = isNegativeCheck(value < 0); // FUN_0064bb50: returns nonzero if value is negative
    if (isNegative) {
        int absValue = -value; // take absolute value
        processCoreData(idx - 1, &absValue); // FUN_0064b810: processes with pointer to absolute value
        return;
    }
    processCoreData(idx - 1, &value); // FUN_0064b810: processes with original value
    return;
}