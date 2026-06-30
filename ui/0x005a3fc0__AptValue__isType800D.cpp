// FUNC_NAME: AptValue::isType800D
bool __thiscall AptValue::isType800D(void *thisPtr) {
    int *exceptionInfo;
    code *debugBreak;
    uint flags;
    uint *thisPtrLocal; // unaff_EDI
    int fsOffset; // unaff_FS_OFFSET
    undefined *assertFile;
    char *assertLine;
    undefined4 assertExpr;
    int assertCode;
    undefined1 *assertFlag;

    if (thisPtr != (void *)0x0) goto checkType;
    // Debug assertion: file, line, expression
    assertFile = &DAT_00e3b9b8; // likely "Assertion failed"
    assertLine = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
    assertExpr = 0x2b0; // line number 688? Actually 0x2b0 = 688
    assertCode = 2;
    assertFlag = &DAT_01128f70;
    if (DAT_01128f70 == '\0') goto checkType;
    // Get exception registration from FS segment
    exceptionInfo = *(int **)(**(int **)(fsOffset + 0x2c) + 0x30);
    flags = 1;
    if (exceptionInfo == (int *)0x0) {
LAB_005a402b:
        if ((flags & 2) != 0) {
            *assertFlag = 0;
        }
    } else {
        flags = (**(code **)(*exceptionInfo + 8))(&assertFile, &DAT_00e3b9b8);
        if (assertFlag != (undefined1 *)0x0) goto LAB_005a402b;
    }
    if (((exceptionInfo != (int *)0x0) || (assertCode != 4)) &&
        (((flags & 1) != 0 || ((assertCode == 0) || (assertCode == 1))))) {
        debugBreak = (code *)swi(3); // Debug breakpoint
        return (*debugBreak)();
    }
checkType:
    // Check if the value at thisPtr is 0x800D (type tag)
    if (((*(uint *)thisPtr & 0x7fff) == 0xd) && ((~(byte)(*(uint *)thisPtr >> 0xf) & 1) == 0)) {
        return 1;
    }
    return 0;
}