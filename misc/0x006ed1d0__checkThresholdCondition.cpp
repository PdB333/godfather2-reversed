// FUNC_NAME: checkThresholdCondition
// Address: 0x006ed1d0
// Role: Compare two input values (a, b) against a threshold, using type-specific comparison functions.
// The first parameter points to a structure: [type (int), a (int), b (int), threshold (union: byte/int/float)]
// The second parameter is an extra contextual value passed to the evaluation functions.

bool checkThresholdCondition(int* data, int extraParam)
{
    int type = data[0];
    int a = data[1];
    int b = data[2];

    if (type == 0)
    {
        // Byte comparison: threshold is low byte of the fourth field
        byte result = evaluateByte(a, b, extraParam);
        byte threshold = (byte)data[3];
        return result < threshold;
    }
    else if (type == 1)
    {
        // Integer comparison
        int result = evaluateInt(a, b, extraParam);
        return result < data[3];
    }
    else if (type == 2)
    {
        // Float comparison: threshold is the IEEE 754 float stored at the fourth field
        float result = evaluateFloat(a, b, extraParam);
        float threshold = *(float*)&data[3];
        return result < threshold;
    }

    return false;
}