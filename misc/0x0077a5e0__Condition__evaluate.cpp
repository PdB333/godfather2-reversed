// FUNC_NAME: Condition::evaluate
// Address: 0x0077a5e0
// Role: Evaluates a generic condition node with comparison (numeric) or logical operations (AND, OR, NOT).
// The object at param_1 has the following layout:
//   +0x00: vtable pointer (not used directly here)
//   +0x04: int32 mOpcode (4=LT,5=GT,6=LE,7=GE,8=EQ,9=AND,10=OR,11=NOT)
//   +0x08: FunctionPointer mFirstGetter – returns float (for numeric) or bool (for logical)
//   +0x0C: FunctionPointer mSecondGetter – returns float (for numeric) or bool (for logical)
//   +0x10: float mCompareValue – stored value for numeric comparisons (offset may vary, assumed here)

bool __thiscall Condition::evaluate(int thisPtr, int param2) {
    int opcode = *(int *)(thisPtr + 4);
    void* firstGetter = *(void **)(thisPtr + 8);
    void* secondGetter = *(void **)(thisPtr + 0xC);
    float compareValue = *(float *)(thisPtr + 0x10); // assumed offset

    bool result = false;
    float10 fVar4; // extended precision temporary

    // Switch on opcode minus 4 to get range 0-7
    switch (opcode - 4) {
        case 0: // LT (opcode 4)
            fVar4 = ((float10 (*)(int))secondGetter)(param2);
            ((void (*)(int))firstGetter)(param2);
            if (compareValue < fVar4) {
                result = true;
            }
            break;
        case 1: // GT (opcode 5)
            fVar4 = ((float10 (*)(int))secondGetter)(param2);
            ((void (*)(int))firstGetter)(param2);
            if (fVar4 < compareValue) {
                result = true;
            }
            break;
        case 2: // LE (opcode 6)
            fVar4 = ((float10 (*)(int))secondGetter)(param2);
            ((void (*)(int))firstGetter)(param2);
            if (compareValue <= fVar4) {
                result = true;
            }
            break;
        case 3: // GE (opcode 7)
            fVar4 = ((float10 (*)(int))secondGetter)(param2);
            ((void (*)(int))firstGetter)(param2);
            if (fVar4 <= compareValue) {
                result = true;
            }
            break;
        case 4: // EQ (opcode 8)
            fVar4 = ((float10 (*)(int))secondGetter)(param2);
            ((void (*)(int))firstGetter)(param2);
            if (compareValue == fVar4) {
                result = true;
            }
            break;
        case 5: // AND (opcode 9)
        {
            char firstResult = ((char (*)(int))firstGetter)(param2);
            if (firstResult == '\0') {
                result = false;
            } else {
                char secondResult = ((char (*)(int))secondGetter)(param2);
                result = (secondResult != '\0');
            }
            break;
        }
        case 6: // OR (opcode 10)
        {
            char firstResult = ((char (*)(int))firstGetter)(param2);
            if (firstResult != '\0') {
                result = true;
            } else {
                char secondResult = ((char (*)(int))secondGetter)(param2);
                result = (secondResult != '\0');
            }
            break;
        }
        case 7: // NOT (opcode 11)
        {
            char firstResult = ((char (*)(int))firstGetter)(param2);
            result = (firstResult == '\0');
            break;
        }
        default:
            // result remains false
            break;
    }
    return result;
}