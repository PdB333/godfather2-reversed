// FUNC_NAME: AptCharacter::setDefaultRect
void AptCharacter::setDefaultRect()
{
    // Assert: this (pRect) must not be null
    if (this == (AptCharacter *)0x0) {
        const char *exprStr = "pRect";
        const char *fileStr = "..\\source\\Apt\\AptCharacter.cpp";
        int lineNum = 0x45a; // 1114
        int assertType = 2;  // probably EA_DEBUG_ASSERT
        char *globalAssertFlag = &DAT_0112912e;
        if (*globalAssertFlag == '\0') goto afterAssert;

        int *moduleDbg = *(int **)(*(int **)(__readfsdword(0x2c) + 0x30) + 0x30); // get debug module
        uint flags = 1;
        if (moduleDbg == (int *)0x0) {
afterAssert:
            if ((flags & 2) != 0) {
                *globalAssertFlag = 0;
            }
        }
        else {
            flags = (**(code **)(*moduleDbg + 8))(&exprStr, "pRect");
            if (globalAssertFlag != (char *)0x0) goto afterAssert;
        }
        if (((moduleDbg != (int *)0x0) || (assertType != 4)) &&
            (((flags & 1) != 0 || ((assertType == 0 || (assertType == 1)))))) {
            // Trigger breakpoint (int 3)
            __debugbreak();
        }
    }

afterAssert:
    // Set rectangle fields from global constants
    int leftVal   = DAT_00e448c8;   // global left/ x
    int topVal    = DAT_00e448c4;   // global top / y
    int rightVal  = DAT_00e448c4;   // same as top? (rectangular? or square)
    int bottomVal = DAT_00e448c4;   // also same

    this->field_0x00 = leftVal;
    this->field_0x04 = topVal;
    this->field_0x08 = rightVal;
    this->field_0x0C = bottomVal;

    // Call helper to finalize (e.g., clamp, convert coordinates)
    FUN_005b5970(DAT_0119cbf0, this);
}