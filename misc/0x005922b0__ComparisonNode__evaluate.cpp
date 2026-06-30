// FUNC_NAME: ComparisonNode::evaluate
// Address: 0x005922b0
// Role: Evaluates two values from string representations or via function calls, then compares them.
//        Returns 1 if left value >= right value, and stores this pointer in outResult[3].
//        The data pair at this+0x8 contains two char* pointers: string1 (offset 0) and string2 (offset 4).
//        If a string starts with '\n', the next two bytes are a short index into a global table
//        (DAT_01205570, entry size 0xC, function pointer at offset 4) to compute the value.
//        Otherwise, the float is read from offset 4 of the string.

int __thiscall ComparisonNode::evaluate(int* outResult)
{
    char* leftStr;
    code* func;
    int idx;
    float leftValue;
    float rightValue;

    // Process left string
    leftStr = *(char**)(**(int**)(this + 8)); // this->m_pDataPair->string1
    if (*leftStr == '\n') {
        idx = *(short*)(leftStr + 2);
        if (idx >= 0 && idx < DAT_01205574) {
            func = *(code**)(DAT_01205570 + 4 + idx * 0xC);
            if (func != nullptr) {
                func(*outResult, idx, &leftValue);
            }
        }
    } else {
        leftValue = *(float*)(leftStr + 4);
    }

    // Process right string
    leftStr = *(char**)(*(int*)(this + 8) + 4); // this->m_pDataPair->string2
    if (*leftStr == '\n') {
        idx = *(short*)(leftStr + 2);
        if (idx >= 0 && idx < DAT_01205574) {
            func = *(code**)(DAT_01205570 + 4 + idx * 0xC);
            if (func != nullptr) {
                func(*outResult, idx, &rightValue);
            }
        }
    } else {
        rightValue = *(float*)(leftStr + 4);
    }

    // Compare and store result
    if (leftValue < rightValue) {
        return 0;
    }
    outResult[3] = (int)this;
    return 1;
}