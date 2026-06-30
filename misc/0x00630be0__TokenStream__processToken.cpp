// FUNC_NAME: TokenStream::processToken
// Address: 0x00630be0
// Role: Reads a token from the read stream, resolves references (type 4) to float values, and writes a flat type-3 token to the write stream. If the float equals a sentinel, it skips following tokens until a non-type-3/4 token.

undefined4 __thiscall TokenStream::processToken(int thisPtr)
{
  undefined4 *writePointer;
  int success;
  int *currentToken;
  float resolvedFloat;
  int referenceBuffer;
  float tempFloat;

  currentToken = *(int **)(thisPtr + 0xc); // read position (current token)
  if (*(int **)(thisPtr + 8) <= currentToken) goto LAB_00630c9b; // check bounds
  if (currentToken == (int *)0x0) goto LAB_00630c9b;

  // Handle token type
  if (*currentToken != 3) {
    if (*currentToken != 4) goto LAB_00630c9b;
    // Type 4: reference token
    success = FUN_00636850(&resolvedFloat); // resolve reference, store float in resolvedFloat
    if (success == 0) goto LAB_00630c9b;
    referenceBuffer = 3; // store a dummy type 3 for the "reference"
    tempFloat = resolvedFloat;
    currentToken = &referenceBuffer; // point to the resolved token
  }

  // Extract the float value from the token (either original or resolved)
  resolvedFloat = (float)currentToken[1];
  if (resolvedFloat == DAT_00e2b05c) {
    // Sentinel match: skip all consecutive type-3 or valid type-4 tokens
    while (true) {
      currentToken = *(int **)(thisPtr + 0xc);
      if (*(int **)(thisPtr + 8) <= currentToken || currentToken == (int *)0x0) break;
      if (*currentToken != 3 && (*currentToken != 4 || (success = FUN_00636850(&referenceBuffer), success == 0))) break;
      FUN_00627ac0(PTR_s_number_00e2a8a8); // log "number" (debug print)
    }
LAB_00630c9b:
    resolvedFloat = 0.0;
  }

  // Write a type-3 token to output buffer
  writePointer = *(undefined4 **)(thisPtr + 8); // write position
  *writePointer = 3;                              // token type
  writePointer[1] = (uint)resolvedFloat & DAT_00e44680; // float converted to int and masked
  *(int *)(thisPtr + 8) = *(int *)(thisPtr + 8) + 8;   // advance write position

  return 1;
}