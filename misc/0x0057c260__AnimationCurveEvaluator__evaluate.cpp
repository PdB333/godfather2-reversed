// FUNC_NAME: AnimationCurveEvaluator::evaluate
void __thiscall AnimationCurveEvaluator::evaluate(int index, int curveType, int extraParam)
{
    // this = in_EAX
    float result;
    float fVar1;
    float fVar2;

    switch (curveType)
    {
    case 1:
        result = evaluateConstant(extraParam);
        *outValue = result;
        return;
    case 2:
        result = evaluateLinear(extraParam);
        *outValue = result;
        return;
    case 3:
        result = evaluateCubic(extraParam);
        *outValue = result;
        return;
    case 4:
        // Direct data read from keyframe storage (32-bit float)
        // in_EAX + 2 + index*4 holds a float
        *outValue = *(float *)((uint8_t*)this + 2 + index * 4);
        return;
    case 6:
    case 7:
        // Interpolation using byte-weight tables
        // Read two 24-bit values from in_EAX + 2 and in_EAX + 5 (big-endian 3-byte fractions?)
        fVar1 = (float)( (*(uint8_t*)((uint8_t*)this + 2) << 16) |
                         (*(uint8_t*)((uint8_t*)this + 3) << 8) |
                          *(uint8_t*)((uint8_t*)this + 4) ) * 256.0f;  // scaled by 256
        fVar2 = (float)( (*(uint8_t*)((uint8_t*)this + 5) << 16) |
                         (*(uint8_t*)((uint8_t*)this + 6) << 8) |
                          *(uint8_t*)((uint8_t*)this + 7) ) * 256.0f;

        if (curveType == 6)
        {
            // Single interpolation weight from table using index
            uint32_t weightIndex = *(uint8_t*)((uint8_t*)this + 8 + index);
            *outValue = gSmoothStepTable[weightIndex] * fVar2 + fVar1;
        }
        else // curveType == 7
        {
            // Double interpolation using two weights
            uint32_t weightIndex1 = *(uint8_t*)((uint8_t*)this + 8 + index * 2);
            uint32_t weightIndex2 = *(uint8_t*)((uint8_t*)this + 9 + index * 2);
            *outValue = (gSmoothStepTable[weightIndex2] * gSecondScaleFactor +
                         gSmoothStepTable[weightIndex1]) * fVar2 + fVar1;
        }
        return;
    default:
        return;
    }
}