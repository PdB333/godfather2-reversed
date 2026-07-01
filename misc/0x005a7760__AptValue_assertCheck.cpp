// FUNC_NAME: AptValue_assertCheck

void AptValue_assertCheck(void)
{
    int *piVar1;
    code *pcVar2;
    char cVar3;
    uint uVar4;
    int fsOffset;
    char *expressionStr; // "isCIH(bUndefOK)"
    char *filePath;
    undefined4 lineNumber;
    int debugFlag;
    undefined1 *assertFlagPtr;

    // Check if assertions are globally disabled
    cVar3 = FUN_0059c5c0(0);
    if (cVar3 != '\0') {
        return;
    }

    // Set up assertion context: expression, file, line, debug level
    expressionStr = "isCIH(bUndefOK)";
    filePath = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
    lineNumber = 0xf6; // 246
    debugFlag = 2;
    assertFlagPtr = &DAT_01128fad;

    // Only proceed if the global assertion flag is set (debug mode)
    if (DAT_01128fad != '\0') {
        // Get the current module's assertion handler from TLS
        piVar1 = *(int **)(**(int **)(fsOffset + 0x2c) + 0x30);
        uVar4 = 1;
        if (((piVar1 == (int *)0x0) ||
            (uVar4 = (**(code **)(*piVar1 + 8))(&expressionStr, "isCIH(bUndefOK)"),
            assertFlagPtr != (undefined1 *)0x0)) && ((uVar4 & 2) != 0)) {
            *assertFlagPtr = 0; // Clear the assertion flag
        }
        // If the assertion handler exists or debug level is 4, and if the check failed, trigger breakpoint
        if (((piVar1 != (int *)0x0) || (debugFlag != 4)) &&
           (((uVar4 & 1) != 0 || ((debugFlag == 0 || (debugFlag == 1)))))) {
            pcVar2 = (code *)swi(3); // Software interrupt 3 (debug break)
            (*pcVar2)();
            return;
        }
        return;
    }
    return;
}