// FUNC_NAME: compareTwoPartValues
/*
 * Function: 0x006edc70
 * Compares two values (each composed of two integer parts) of varying types (byte, int, float).
 * The type selector at offset 0 determines how the parts are interpreted.
 * param_1 points to a struct with fields: type (int), firstValPart1, firstValPart2, secondValPart1, secondValPart2.
 * param_2 is a context pointer passed to the helper functions that compute scalar values from the parts.
 */

typedef unsigned char byte;

// Helper function declarations (not defined here)
byte computeByteValue(int part1, int part2, void* context);
int computeIntValue(int part1, int part2, void* context);
float computeFloatValue(int part1, int part2, void* context);

bool compareTwoPartValues(int* data, void* context)
{
    // data layout: [type, firstPart1, firstPart2, secondPart1, secondPart2]
    int type = data[0];
    int firstPart1 = data[1];
    int firstPart2 = data[2];
    int secondPart1 = data[3];
    int secondPart2 = data[4];

    bool result = false;

    if (type == 0) // Byte comparison
    {
        byte val1 = computeByteValue(firstPart1, firstPart2, context);
        byte val2 = computeByteValue(secondPart1, secondPart2, context);
        result = (val1 <= val2);
    }
    else if (type == 1) // Integer comparison
    {
        int val1 = computeIntValue(firstPart1, firstPart2, context);
        int val2 = computeIntValue(secondPart1, secondPart2, context);
        result = (val1 <= val2);
    }
    else if (type == 2) // Float comparison
    {
        float val1 = computeFloatValue(firstPart1, firstPart2, context);
        float val2 = computeFloatValue(secondPart1, secondPart2, context);
        result = (val1 <= val2);
    }

    return result;
}