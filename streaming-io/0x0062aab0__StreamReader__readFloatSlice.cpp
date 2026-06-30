// FUNC_NAME: StreamReader::readFloatSlice
// Address: 0x0062aab0
// This function reads a series of tokens from a binary stream, extracts float values,
// and writes a new token representing a slice of the float range. It handles token types 3 and 4.
// The structure at param_1 (this) contains buffer pointers:
//   +0x08: end buffer pointer
//   +0x0c: current read pointer
//   +0x10: pointer to a buffer manager (likely with overrun protection at offsets +0x20 and +0x24)

int StreamReader::readFloatSlice()
{
  int *currentToken;
  int tokenValue;
  int index;
  float firstFloat;
  float secondFloat;
  float sliceStart;
  float sliceLength;
  int local_14;
  int stack_10;
  float stack_c;

  // --- First token read: try to get a float value (or parse token type) ---
  currentToken = *(int **)(this + 0xc);
  if ((currentToken < *(int **)(this + 0x8)) && (currentToken != (int *)0x0)) {
    if (*currentToken == 4) {
      // Token type 4: direct float value stored at offset +0x04 (as int)
      index = currentToken[1] + 0x10;   // ??? likely offset to actual float value
    }
    else {
      // Not type 4: try to parse the token string to float
      index = FUN_00633990(this);
      if (index == 0) {
        index = 0;
      }
      else {
        index = currentToken[1] + 0x10; // conversion succeeded, use the offset
      }
      // Check for buffer overrun via manager at +0x10
      if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24)) {
        FUN_00627360(); // likely assertion failure or debug break
      }
    }
    local_14 = index;
    if (index != 0) goto GOT_FIRST;
  }
  // If we couldn't read first token, emit error string
  FUN_00627ac0(PTR_s_string_00e2a8ac);
GOT_FIRST:
  // Extract the actual float value from the first token's data (if applicable)
  currentToken = *(int **)(this + 0xc);
  if ((currentToken < *(int **)(this + 0x8)) && (currentToken != (int *)0x0)) {
    if (*currentToken == 4) {
      firstFloat = *(float *)(currentToken[1] + 0xc);
    }
    else {
      index = FUN_00633990(this);
      if (index == 0) {
        firstFloat = 0.0f;
      }
      else {
        firstFloat = *(float *)(currentToken[1] + 0xc);
      }
    }
  }
  else {
    firstFloat = 0.0f;
  }

  // --- Second token read: expect a token of type 3 (range?) or type 4 (float) ---
  currentToken = (int *)(*(int *)(this + 0xc) + 8);
  if ((*(int **)(this + 0x8) <= currentToken) || (currentToken == (int *)0x0)) goto LAB_FALLBACK;
  if (*currentToken != 3) {
    if (*currentToken != 4) goto LAB_FALLBACK; // not a valid token type
    // Token type 4: try to interpret it as a float
    index = FUN_00636850(&stack_c); // maybe reads a boolean or checks if valid
    if (index == 0) goto LAB_FALLBACK;
    stack_10 = 3;
    stack_c = stack_c; // ??? this assignment seems redundant
    currentToken = &stack_10;
  }
  // currentToken now points to a type-3 token (or we faked one)
  sliceStart = (float)currentToken[1]; // value of the second token
  secondFloat = sliceStart;

  // Check if firstFloat equals a known global constant (maybe "special" marker)
  if (firstFloat == DAT_00e2b05c) {
    // If special marker, keep reading tokens until we find a numeric one (type 3 or 4)
    while (true) {
      currentToken = (int *)(*(int *)(this + 0xc) + 8);
      if ((*(int **)(this + 0x8) <= currentToken) || (currentToken == (int *)0x0)) break;
      if (*currentToken != 3) {
        if (*currentToken != 4) break;
        index = FUN_00636850(&stack_10);
        secondFloat = sliceStart; // retain the value from previous token
        if (index == 0) break;
      }
      // Found a numeric token, exit loop
      break;
    }
    // If loop ended without finding, emit error
    if ((*(int **)(this + 0x8) <= currentToken) || (currentToken == (int *)0x0) ||
        ((*currentToken != 3 && (*currentToken != 4 || (index = FUN_00636850(&stack_10), secondFloat = sliceStart, index == 0))))) {
      index = 2;
      FUN_00627ac0(PTR_s_number_00e2a8a8); // string "number"
      goto LAB_FALLBACK;
    }
  }
LAB_FALLBACK:
  sliceStart = 0.0f;

  // --- Calculations ---
  sliceStart = (float)(int)secondFloat; // truncate to integer
  if ((int)sliceStart < 0) {
    sliceStart = (float)((int)sliceStart + 1 + index); // adjust for negative? index is from previous loop
  }

  // Check a fourth token at offset +0x10 (maybe a boolean flag)
  currentToken = (int *)(*(int *)(this + 0xc) + 0x10);
  float modifiedFloat = DAT_00e2eff4; // global constant
  if ((currentToken < *(int **)(this + 0x8)) && (currentToken != (int *)0x0) && (0 < *currentToken)) {
    // If the token exists and is positive, call some function
    FUN_00628080();
    modifiedFloat = secondFloat; // override with second float
  }

  index = (int)modifiedFloat;
  if (index < 0) {
    index = index + 1 + index; // ??? this looks like a bug in decompiler: should be index = index + 1 + (some other value)
  }

  if ((int)sliceStart < 1) {
    sliceStart = 1.4013e-45; // min float positive denormal? Likely a small epsilon
  }

  int bufferManager = *(int *)(this + 0x10);
  if (index < local_14) {
    index = local_14; // ?? Seems reversed - probably intended to be min?
  }

  // Emit a new token of type 4 (float value)
  int baseValue = local_14 - 1 + (int)sliceStart;
  int count = (index - (int)sliceStart) + 1;
  if (count < 0) { // This is inferred from the condition: if (index < (int)sliceStart) ...
    // Actually the original code has: if (iVar4 < (int)fStack_18) { ... emit token ... }
    // then else { emit different token }. So the logic is different.
    // Let's re-evaluate: 
    // The original code:
    //   iVar4 = (int)fVar8;  // fVar8 is modifiedFloat or secondFloat or something
    //   if (iVar4 < 0) { iVar4 = iVar4 + 1 + iVar6; }
    //   if ((int)fStack_18 < 1) { fStack_18 = 1.4013e-45; }
    //   iVar1 = *(int *)(param_1 + 0x10);
    //   if (iVar6 < iVar4) { iVar4 = iVar6; } // min(iVar6, iVar4)
    //   if (iVar4 < (int)fStack_18) { // iVar4 < sliceStart
    //     ... emit token with base = sliceStart-1, count = (iVar4 - sliceStart)+1 (likely 0 or negative)
    //   } else {
    //     ... emit token with base = local_14 -1 + sliceStart, count = (iVar4 - sliceStart)+1
    //   }
    // So it checks if iVar4 (the computed upper bound) is less than sliceStart. 
    // That is strange: if the computed range is empty, it emits a token with a negative count?
    // Possibly this handles overflow/negative ranges.
  }

  // Write token to output buffer
  int *currentWrite = *(int **)(this + 0x8);
  if (index < (int)sliceStart) {
    // Case: range start > end (empty or negative length)
    if (*(uint *)(bufferManager + 0x20) <= *(uint *)(bufferManager + 0x24)) {
      FUN_00627360(); // assert buffer space
    }
    *currentWrite = 4; // token type 4
    currentWrite[1] = FUN_00638920(this, &DAT_00e2f044, 0); // ??? possibly a special token value
    *(int *)(this + 0x8) += 8;
    return 1;
  }
  else {
    // Normal case: valid range
    if (*(uint *)(bufferManager + 0x20) <= *(uint *)(bufferManager + 0x24)) {
      FUN_00627360();
    }
    *currentWrite = 4;
    baseValue = local_14 - 1 + (int)sliceStart;
    count = (index - (int)sliceStart) + 1;
    currentWrite[1] = FUN_00638920(this, baseValue, count);
    *(int *)(this + 0x8) += 8;
    return 1;
  }
}