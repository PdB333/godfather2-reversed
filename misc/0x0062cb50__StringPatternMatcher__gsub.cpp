// FUNC_NAME: StringPatternMatcher::gsub
undefined4 StringPatternMatcher::gsub(int matchContext)

{
  char patternChar;
  undefined4 *resultStack;
  code *errorFunc;
  int typeCheck;
  int *iteratorPtr;
  undefined1 *captureEnd;
  int charCount;
  int *tempPtr;
  float floatMaxCount;
  float fVar10;
  undefined1 *inputStart;
  int inputLength;
  undefined1 *local_334;
  char *patternStr;
  undefined1 *outputPtr;
  undefined4 uStack_324;
  int replacementCount;
  undefined1 outputBuffer [512];
  undefined1 local_11c [4];
  undefined1 *bufStart;
  undefined1 *bufEnd;
  int bufferMeta;
  undefined4 uStack_10c;
  
  iteratorPtr = *(int **)(matchContext + 0xc);
  if ((iteratorPtr < *(int **)(matchContext + 8)) && (iteratorPtr != (int *)0x0)) {
    if (*iteratorPtr == 4) {
      inputStart = (undefined1 *)(iteratorPtr[1] + 0x10);
    }
    else {
      typeCheck = FUN_00633990(matchContext);  // check if it's a string type
      if (typeCheck == 0) {
        inputStart = (undefined1 *)0x0;
      }
      else {
        inputStart = (undefined1 *)(iteratorPtr[1] + 0x10);
      }
      // check buffer capacity vs size
      if (*(uint *)(*(int *)(matchContext + 0x10) + 0x20) <= *(uint *)(*(int *)(matchContext + 0x10) + 0x24))
      {
        FUN_00627360();  // probably luaD_throw
      }
    }
    local_334 = inputStart;
    if (inputStart == (undefined1 *)0x0) goto LAB_0062cbb2;
  }
  else {
LAB_0062cbb2:
    inputStart = (undefined1 *)0x1;
    FUN_00627ac0(PTR_s_string_00e2a8ac);  // error: "string expected"
  }
  // Get input length
  iteratorPtr = *(int **)(matchContext + 0xc);
  if ((iteratorPtr < *(int **)(matchContext + 8)) && (iteratorPtr != (int *)0x0)) {
    if (*iteratorPtr == 4) {
      inputLength = *(int *)(iteratorPtr[1] + 0xc);
    }
    else {
      typeCheck = FUN_00633990(matchContext);
      if (typeCheck == 0) {
        inputLength = 0;
      }
      else {
        inputLength = *(int *)(iteratorPtr[1] + 0xc);
      }
    }
  }
  else {
    inputLength = 0;
  }
  // Get pattern string
  int iVar7 = *(int *)(matchContext + 0xc);
  iteratorPtr = (int *)(iVar7 + 8);
  if ((iteratorPtr < *(int **)(matchContext + 8)) && (iteratorPtr != (int *)0x0)) {
    if (*iteratorPtr == 4) {
      patternStr = (char *)(*(int *)(iVar7 + 0xc) + 0x10);
    }
    else {
      typeCheck = FUN_00633990(matchContext);
      if (typeCheck == 0) {
        patternStr = (char *)0x0;
      }
      else {
        patternStr = (char *)(*(int *)(iVar7 + 0xc) + 0x10);
      }
      if (*(uint *)(*(int *)(matchContext + 0x10) + 0x20) <= *(uint *)(*(int *)(matchContext + 0x10) + 0x24))
      {
        FUN_00627360();
      }
    }
    if (patternStr != (char *)0x0) goto LAB_0062cc69;
  }
  patternStr = (char *)0x2;
  FUN_00627ac0(PTR_s_string_00e2a8ac);
LAB_0062cc69:
  // max replacement count (float conversion)
  fVar10 = (float)(inputLength + 1);
  if (inputLength + 1 < 0) {
    fVar10 = fVar10 + DAT_00e44578;
  }
  // Read optional 4th value (replacement function/string)
  iteratorPtr = (int *)(*(int *)(matchContext + 0xc) + 0x18);
  if (((iteratorPtr < *(int **)(matchContext + 8)) && (iteratorPtr != (int *)0x0)) && (0 < *iteratorPtr)) {
    FUN_00628080();  // likely reads a number from stack
    fVar10 = in_XMM0_Da;
  }
  // Check pattern anchor '^'
  patternChar = *patternStr;
  if (patternChar == '^') {
    patternStr = patternStr + 1;
  }
  // Validate that we have a string or function for replacement
  iteratorPtr = *(int **)(matchContext + 8);
  replacementCount = 0;
  if ((((int)((int)iteratorPtr - *(int *)(matchContext + 0xc) & 0xfffffff8U) < 0x18) ||
      (tempPtr = (int *)(*(int *)(matchContext + 0xc) + 0x10), iteratorPtr <= tempPtr)) ||
     (((tempPtr == (int *)0x0 || ((*tempPtr != 4 && (*tempPtr != 3)))) &&
      ((iteratorPtr <= tempPtr || ((tempPtr == (int *)0x0 || (*tempPtr != 6)))))))) {
    FUN_00627a20(matchContext,3,"string or function expected");
    errorFunc = (code *)swi(3);
    uVar8 = (*errorFunc)();
    return uVar8;
  }
  // Setup output buffer pointers
  outputPtr = (undefined1 *)outputBuffer;
  bufStart = inputStart;
  bufEnd = inputStart + inputLength;
  bufferMeta = matchContext;
  uStack_324 = 0;
  int bufferMeta2 = matchContext;
  floatMaxCount = fVar10;
  if ((int)fVar10 < 1) {
LAB_0062ce1e:
    // Append remaining input after last match
    FUN_00628b20(inputStart,(int)bufEnd - (int)inputStart);
    FUN_00628940();  // check buffer overflow?
    FUN_00626460();  // finalize output string
    resultStack = *(undefined4 **)(matchContext + 8);
    *resultStack = 3;           // type: string
    resultStack[1] = (float)replacementCount;
    *(int *)(matchContext + 8) = *(int *)(matchContext + 8) + 8;
    return 2;
  }
  do {
    uStack_10c = 0;
    captureEnd = (undefined1 *)FUN_0062bd60(&bufStart, inputStart, patternStr);
    if (captureEnd == (undefined1 *)0x0) {
LAB_0062cdba:
      if (bufEnd <= inputStart) goto LAB_0062ce1e;
      if (local_11c <= outputPtr) {
        int overflow = FUN_00628940();
        if (overflow != 0) {
          FUN_006289a0(&outputPtr);
        }
      }
      *outputPtr = *inputStart;
      outputPtr = outputPtr + 1;
      captureEnd = inputStart + 1;
    }
    else {
      replacementCount = replacementCount + 1;
      FUN_0062c970(&bufStart, &outputPtr, inputStart, captureEnd);
      if (captureEnd <= inputStart) goto LAB_0062cdba;
    }
    inputStart = captureEnd;
    if ((patternChar == '^') || ((int)floatMaxCount <= replacementCount)) goto LAB_0062ce1e;
  } while( true );
}