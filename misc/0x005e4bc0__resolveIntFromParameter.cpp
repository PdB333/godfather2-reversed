// FUNC_NAME: resolveIntFromParameter
int __fastcall resolveIntFromParameter(int unused, int parameterString, int objectPtr, int additionalData)
{
    int result = 0;
    int intValue = 0;
    char dummy; // not used, likely a buffer for string parsing
    bool success = FUN_005f0560(parameterString, &dummy, &intValue); // parse string to get integer value
    if (success && intValue != 0) {
        result = FUN_005e4a80(objectPtr, intValue, additionalData); // create/retrieve something using the integer
        return result;
    }
    return 0;
}