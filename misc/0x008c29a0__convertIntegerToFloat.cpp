// FUNC_NAME: convertIntegerToFloat
void convertIntegerToFloat(int intValue, uint someArg)
{
    // Convert integer to float, handling negative values as unsigned representation
    // (intValue < 0) indicates a two's complement negative, so we add 2^32 to get the correct float value
    float floatValue = (float)intValue;
    if (intValue < 0) {
        floatValue = floatValue + kTwoPow32; // DAT_00e44578 = 4294967296.0f
    }
    FUN_008c09a0(floatValue, someArg);
}