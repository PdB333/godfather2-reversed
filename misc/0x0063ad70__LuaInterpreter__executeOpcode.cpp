// FUNC_NAME: LuaInterpreter::executeOpcode
undefined4 LuaInterpreter::executeOpcode(int interpreter) {
  int opcode;
  int *stackPtr;
  undefined4 *value1;
  int *stackTop;
  undefined4 *value2;
  int extraData;
  
  // Push a constant string or value onto the stack
  FUN_00625ca0(interpreter, &DAT_00e416ec);
  extraData = *(int *)(interpreter + 8);
  opcode = *(int *)(extraData + -8);
  if (opcode == 3) {
    if ((float)(int)*(float *)(extraData + -4) != *(float *)(extraData + -4)) goto LAB_0063adc6;
    stackTop = (int *)FUN_00637f10(); // Get float operation function
  }
  else if (opcode == 4) {
    stackTop = (int *)FUN_00637f90(); // Get string operation function
  }
  else {
LAB_0063adc6:
    stackTop = (int *)FUN_00637ea0(); // Get generic operation function
  }
  *(int *)(extraData + -8) = *stackTop;
  *(int *)(extraData + -4) = stackTop[1];
  stackPtr = *(int **)(interpreter + 8);
  if ((stackPtr + -2 != (int *)0x0) && (stackPtr[-2] == 5)) {
    extraData = *(int *)(interpreter + 0xc);
    *stackPtr = *(int *)(extraData + 8);
    stackPtr[1] = *(int *)(extraData + 0xc);
    *(int *)(interpreter + 8) = *(int *)(interpreter + 8) + 8; // Pop two stack slots
    FUN_00625e70(); // Stack management
    stackPtr = *(int **)(interpreter + 8);
    stackTop = stackPtr + -2;
    if (stackTop != (int *)0x0) {
      if ((*stackTop == 6) && (*(char *)(stackPtr[-1] + 6) != '\0')) {
        FUN_006362d0(interpreter, stackTop, 1);
        return 1;
      }
      if ((stackTop != (int *)0x0) && (*stackTop == 5)) {
        return 1;
      }
    }
  }
  stackTop = *(int **)(interpreter + 0xc);
  if ((stackTop < stackPtr) && (stackTop != (int *)0x0)) {
    if (*stackTop == 5) {
      extraData = *(int *)(stackTop[1] + 8);
    }
    else {
      if (*stackTop != 7) goto LAB_0063af2f;
      extraData = *(int *)(stackTop[1] + 8);
    }
    if ((extraData != 0) && (extraData != *(int *)(*(int *)(interpreter + 0x10) + 0x38))) {
      *stackPtr = 5;
      stackPtr[1] = extraData;
      *(int *)(interpreter + 8) = *(int *)(interpreter + 8) + 8; // Push key onto stack
      FUN_00625ca0(interpreter, "__index"); // Metamethod call
      FUN_00625e70(); // Stack management
      value2 = *(undefined4 **)(interpreter + 0xc);
      value1 = *(undefined4 **)(interpreter + 8);
      *value1 = *value2;
      value1[1] = value2[1];
      *(int *)(interpreter + 8) = *(int *)(interpreter + 8) + 8; // Copy table value
      extraData = *(int *)(interpreter + 0xc);
      value2 = *(undefined4 **)(interpreter + 8);
      *value2 = *(undefined4 *)(extraData + 8);
      value2[1] = *(undefined4 *)(extraData + 0xc);
      *(int *)(interpreter + 8) = *(int *)(interpreter + 8) + 8; // Copy second part
      extraData = *(int *)(interpreter + 8);
      stackTop = (int *)(extraData + -8);
      if (stackTop != (int *)0x0) {
        if (*stackTop == 6) {
          FUN_006362d0(interpreter, extraData + -0x18, 1);
          return 1;
        }
        if ((stackTop != (int *)0x0) && (*stackTop == 5)) {
          value2 = (undefined4 *)FUN_00633cb0(interpreter, extraData + -0x18, stackTop, 0);
          extraData = *(int *)(interpreter + 8);
          *(undefined4 *)(extraData + -8) = *value2;
          *(undefined4 *)(extraData + -4) = value2[1];
          return 1;
        }
      }
    }
  }
LAB_0063af2f:
  **(undefined4 **)(interpreter + 8) = 0; // Push nil
  *(int *)(interpreter + 8) = *(int *)(interpreter + 8) + 8;
  return 1;
}