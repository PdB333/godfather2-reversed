// Xbox PDB: AptActionInterpreter::stackPush
// FUNC_NAME: AptAction::applyValue
void __thiscall AptAction::applyValue(int value) {
    // Assertion check: if value is null, assert that pValue is not null
    if (value != 0) goto LAB_005a42a6;

    // Debug assertion (from _AptActions.h line 0xec)
    const char* pValue = "pValue";
    const char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptActions.h";
    int line = 0xec;
    int severity = 2;
    bool* assertFlag = (bool*)&DAT_01128f73;
    if (*assertFlag) {
        // Get thread-local assert handler
        int* handler = *(int**)(*(int**)(__readfsdword(0x2c) + 0x30) + 0x30);
        uint flags = 1;
        if (handler != nullptr) {
            flags = (**(code**)(*handler + 8))(&pValue, "pValue");
            if (assertFlag != nullptr) {
                if ((flags & 2) != 0) {
                    *assertFlag = false;
                }
            }
        } else {
            if ((flags & 2) != 0) {
                *assertFlag = false;
            }
        }
        // If assertion fails, break into debugger
        if ((handler != nullptr) || (severity == 4)) {
            if ((flags & 1) == 0 && (severity != 0 && severity != 1)) {
                // Continue
            } else {
                ((code*)swi(3))(); // Debug break
            }
        }
    }

LAB_005a42a6:
    if (isFirstCondition()) {
        int index = getFirstIndex();
        setIntProperty(*(int*)(*(int*)(this + 0x818) + *(int*)(index + 4) * 4));
        return;
    }
    if (isSecondCondition()) {
        int index = getSecondIndex();
        setIntProperty(*(int*)(this + 0x820 + *(int*)(index + 4) * 4));
        return;
    }
    setIntProperty(value);
}