// FUNC_NAME: SomeClass::remapValue
float __fastcall SomeClass::remapValue(void* thisPtr)
{
    // thisPtr points to an object with a pointer at +0x4 to another structure
    // that structure has a float at +0x48
    float inputValue = *(float*)(*(int*)((char*)thisPtr + 4) + 0x48);

    // Clamp inputValue between DAT_00d5ef88 and DAT_00d70058
    float clamped;
    if (inputValue <= DAT_00d70058) {
        if (DAT_00d5ef88 <= inputValue) {
            clamped = inputValue;
        } else {
            clamped = DAT_00d5ef88;
        }
    } else {
        clamped = DAT_00d70058;
    }

    // Linear remap: ((clamped - minInput) / inputRange) * outputRange + outputMin
    // Constants: DAT_00d5ef88 = minInput, DAT_00e53684 = inputRange,
    //            DAT_00e53688 = outputRange, DAT_00d5cf70 = outputMin
    return ((float)clamped - (float)DAT_00d5ef88) / (float)DAT_00e53684 * (float)DAT_00e53688 + (float)DAT_00d5cf70;
}