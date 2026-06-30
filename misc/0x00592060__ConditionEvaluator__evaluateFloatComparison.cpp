// FUNC_NAME: ConditionEvaluator::evaluateFloatComparison
bool __thiscall ConditionEvaluator::evaluateFloatComparison(int this, ScriptValue* result)
{
    // +0x8: pointer to a FloatTokenPair? First token pointer.
    uint8_t* tokenData1 = **(uint8_t***)(this + 8);
    float valueA;
    if (tokenData1[0] == '\n') 
    {
        // Token is an index into a function table to retrieve a float.
        int16_t index = *(int16_t*)(tokenData1 + 2);
        if (index >= 0 && index < g_floatGetterCount) 
        {
            FloatGetter* getter = g_floatGetters[index];
            if (getter != nullptr) 
            {
                getter->func(*result->context, index, &valueA);
            }
        }
    }
    else 
    {
        // Token is a literal float stored at offset 4.
        valueA = *(float*)(tokenData1 + 4);
    }

    // Next token: offset 4 from the first token data pointer? Actually from the structure at this+8, second element.
    uint8_t* tokenData2 = *(uint8_t**)(*(int*)(this + 8) + 4);
    float valueB;
    if (tokenData2[0] == '\n') 
    {
        int16_t index = *(int16_t*)(tokenData2 + 2);
        if (index >= 0 && index < g_floatGetterCount) 
        {
            FloatGetter* getter = g_floatGetters[index];
            if (getter != nullptr) 
            {
                getter->func(*result->context, index, &valueB);
            }
        }
    }
    else 
    {
        valueB = *(float*)(tokenData2 + 4);
    }

    // Build comparison result flags.
    // Flag bits: bit0 = less, bit1 = ?, bit2 = NaN, bit6 = equal (shifted later).
    uint32_t flags = 2 | (valueA < valueB) | (isnan(valueA) || isnan(valueB)) << 2;
    if (valueA == valueB) 
    {
        flags |= 0x40; // equal flag?
        return (uint32_t)(flags << 8); // return result shifted? Possibly boolean.
    }

    result[3] = this; // Store this pointer in result output.
    return 1 | (flags << 8);
}