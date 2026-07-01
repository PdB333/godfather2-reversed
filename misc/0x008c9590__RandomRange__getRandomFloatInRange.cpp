// FUNC_NAME: RandomRange::getRandomFloatInRange
float __fastcall RandomRange::getRandomFloatInRange(int this)
{
    float minVal;
    float maxVal;
    int randomInt;
    
    minVal = *(float *)(this + 0x3c); // +0x3c: max value of range
    maxVal = *(float *)(this + 0x38); // +0x38: min value of range
    randomInt = _rand();
    return (float)randomInt * (float)DAT_00e44590 * (float)(minVal - maxVal) +
           (float)*(float *)(this + 0x38); // Scale random to range [min, max]
}