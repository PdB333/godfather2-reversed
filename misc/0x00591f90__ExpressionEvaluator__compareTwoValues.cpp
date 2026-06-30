// FUNC_NAME: ExpressionEvaluator::compareTwoValues

int __thiscall ExpressionEvaluator::compareTwoValues(ExpressionContext *this, ExpressionResult *resultOut)
{
    uint comparisonFlags;
    int funcIndex;
    code *funcPtr;
    char *desc;
    float leftValue[3];
    float rightValue[3];

    // Read left value descriptor
    desc = *(char **)this->valueDescriptor;  // +0x08 is a pointer to descriptor struct? Actually offset 8 is a pointer to a descriptor block
    if (*desc == '\n') {
        // Indexed script function: get float via lookup
        funcIndex = *(short *)(desc + 2);  // index stored as short
        if (funcIndex >= 0 && funcIndex < g_functionTableSize) {
            funcPtr = *(code **)(g_functionTable + 4 + funcIndex * 12);  // Each entry 12 bytes, function pointer at +4
            if (funcPtr != nullptr) {
                funcPtr(*resultOut->context, funcIndex, leftValue);  // Call function to fetch float
            }
        }
    } else {
        // Direct float literal at offset 4
        leftValue[0] = *(float *)(desc + 4);
    }

    // Read right value descriptor
    desc = *(char **)(*(int *)(this->valueDescriptor) + 4);  // Second descriptor is offset 4 from the first descriptor block
    if (*desc == '\n') {
        funcIndex = *(short *)(desc + 2);
        if (funcIndex >= 0 && funcIndex < g_functionTableSize) {
            funcPtr = *(code **)(g_functionTable + 4 + funcIndex * 12);
            if (funcPtr != nullptr) {
                funcPtr(*resultOut->context, funcIndex, rightValue);  // Result stored as char*? Actually fd returns something but cast to char*
            }
        }
    } else {
        rightValue[0] = *(float *)(desc + 4);
    }

    // Build comparison flags
    // Low byte: bits: bit0 = less-than, bit1 = always set (2U), bit2 = NaN (either), bit6 = equal
    // High 16 bits: derived from the second descriptor pointer (pcVar4) high word
    comparisonFlags = CONCAT21((short)((uint)desc >> 16),
                                (leftValue[0] == rightValue[0]) << 6 |
                                (NAN(leftValue[0]) || NAN(rightValue[0])) << 2 |
                                2U | 
                                (leftValue[0] < rightValue[0]));

    if (leftValue[0] != rightValue[0]) {
        return (int)(comparisonFlags << 8);  // Return high byte shifted
    }
    // Equal: store this pointer in resultOut[3] and combine with 1
    resultOut[3].ptr = this;  // +0x0C offset
    return CONCAT31(comparisonFlags, 1);  // Append 1 to low byte
}