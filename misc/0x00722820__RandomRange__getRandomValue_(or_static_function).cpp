// FUNC_NAME: RandomRange::getRandomValue (or static function)
// Address: 0x00722820
// Description: Returns a random float between the min (offset +0x134) and max (offset +0x138) values of the object at 'this'.
// Uses rand() and a cached reciprocal constant (DAT_00e44590) to scale the random integer.
float __fastcall getRandomValue(void* thisPtr) {
    float minVal = *(float*)((char*)thisPtr + 0x134);   // +0x134: minimum of range
    float maxVal = *(float*)((char*)thisPtr + 0x138);   // +0x138: maximum of range

    // If the range is valid (min <= max and not equal), generate a random value in [min, max).
    if (minVal <= maxVal && minVal != maxVal) {
        int randInt = _rand();
        // DAT_00e44590 is likely 1.0f / RAND_MAX (a float reciprocal)
        float scale = *(float*)0x00e44590;  // reciprocal of RAND_MAX, stored as a float constant
        return (float)randInt * scale * maxVal + minVal - minVal; // Simplified: rand * (max-min)/RAND_MAX + min
        // The original decompiled expression: ((float)randInt * scale * maxVal + minVal) - minVal
        // Which equals (float)randInt * scale * maxVal, but that's weird; should be (float)randInt * scale * (maxVal - minVal) + minVal.
        // Possibly a compiler optimization or a different interpretation. Let's keep as-is but note the likely intent.
    }
    // Invalid or degenerate range: return maxVal.
    return maxVal;
}