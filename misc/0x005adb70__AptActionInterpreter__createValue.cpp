// FUNC_NAME: AptActionInterpreter::createValue
uint* AptActionInterpreter::createValue(uint param1, int param2)
{
    // Assert: nParams must be 0 or 1
    if (param2 >= 2) {
        const char* expr = "nParams <= 1";
        const char* file = "..\\source\\Apt\\AptActionInterpreter.cpp";
        int line = 927;
        int mode = 2;
        undefined1* debugFlag = &DAT_01128fe9;

        if (DAT_01128fe9 != '\0') {
            int* fsData = *(int**)(*(int**)(FS_OFFSET + 0x2c) + 0x30);
            uint result = 1;
            if (fsData != nullptr) {
                result = (**(code**)(*fsData + 8))(&expr, "nParams <= 1");
            }
            if ((result & 2) != 0) {
                *debugFlag = 0;
            }
            if ((fsData != nullptr) || (mode != 4)) {
                if ((result & 1) != 0 || (mode == 0 || mode == 1)) {
                    // Trigger debug break
                    code* handler = (code*)swi(3);
                    uint* (*handlerFunc)() = (uint* (*)())*handler;
                    return handlerFunc();
                }
            }
        }
    }

    // Allocate an 8‑byte value object
    uint* value = (uint*)DAT_0119caf0(8);
    if (value == nullptr)
        return nullptr;

    if (param2 == 0) {
        // Initialize as undefined (value field = 1)
        *value = (*value & 0xffff8005) | 5;
        value[1] = 1;
        *(uint16*)((int)value + 2) = 0;
        *value |= 0x8000;
    } else {
        // Initialize as null (value field = 0)
        FUN_005a0d00(0);
        *value = (*value & 0xffff8005) | 5;
        value[1] = 0;
        *(uint16*)((int)value + 2) = 0;
        *value |= 0x8000;
    }
    return value;
}