// FUNC_NAME: ScriptTokenizer::reduceExponentToken
undefined4 __thiscall ScriptTokenizer::reduceExponentToken(TokenStream* thisPtr)
{
    int* tokenPtr;
    int tokenType;
    int exponentType;
    float exponentVal;
    float mantissaVal;
    int tempType;
    float tempVal;

    // Start by reading exponent: tokenPtr = limit + 8? Actually thisPtr+0xc is limit, tokenPtr points to end+8 (beyond buffer?)
    tokenPtr = (int*)(*(int*)(thisPtr + 0xc) + 8);
    tokenType = 3; // default target type
    if (*(int**)(thisPtr + 8) <= tokenPtr) goto LAB_006321f0;
    if (tokenPtr == (int*)0x0) goto LAB_006321f0;
    if (*tokenPtr != 3) {
        if (*tokenPtr != 4) goto LAB_006321f0;
        // Type 4 token, check validity via FUN_00636850
        if (!FUN_00636850(&exponentVal)) goto LAB_006321f0;
        tempType = 3;
        tempVal = exponentVal;
        tokenPtr = &tempType; // fake token for loop condition? This allows reading as type 3
    }
    exponentVal = (float)tokenPtr[1]; // value of exponent token
    if (exponentVal == DAT_00e2b05c) {
        // Exponent is sentinel (0.0?), try to find next valid exponent token
        while (true) {
            tokenPtr = (int*)(*(int*)(thisPtr + 0xc) + 8);
            if (*(int**)(thisPtr + 8) <= tokenPtr || tokenPtr == (int*)0x0) goto invalid_exponent;
            if (*tokenPtr == tokenType) break;
            if (*tokenPtr == 4 && FUN_00636850(&tempVal)) break;
invalid_exponent:
            tokenType = 2;
            FUN_00627ac0(PTR_s_number_00e2a8a8); // print "number"
            exponentVal = 0.0f;
        }
    }
    // Now read mantissa token from beginning of stream? Note: tokenPtr is reassigned from thisPtr+0xc again?? Logic seems duplicated.
    // Actually the second read uses thisPtr+0xc (limit) not current pointer. Strange.
    tokenPtr = *(int**)(thisPtr + 0xc);
    tokenType = 3; // reset type
    if (*(int**)(thisPtr + 8) <= tokenPtr) goto LAB_006322a1;
    if (tokenPtr == (int*)0x0) goto LAB_006322a1;
    if (*tokenPtr != 3) {
        if (*tokenPtr != 4) goto LAB_006322a1;
        if (!FUN_00636850(&mantissaVal)) goto LAB_006322a1;
        tempVal = mantissaVal;
        tokenPtr = &tempType;
        tempType = 3;
    }
    mantissaVal = (float)tokenPtr[1];
    if (mantissaVal == DAT_00e2b05c) {
        while (true) {
            tokenPtr = *(int**)(thisPtr + 0xc);
            if (*(int**)(thisPtr + 8) <= tokenPtr || tokenPtr == (int*)0x0) goto invalid_mantissa;
            if (*tokenPtr == tokenType) break;
            if (*tokenPtr == 4 && FUN_00636850(&tempType)) break; // note: parameter is &tempType (int?), likely bug or different function usage
invalid_mantissa:
            tokenType = 1;
            FUN_00627ac0(PTR_s_number_00e2a8a8);
            mantissaVal = 0.0f;
        }
    }
    // Compute number = mantissa * 2^exponent (ldexp)
    double result = _ldexp((double)mantissaVal, (int)exponentVal);
    // Write resulting token at current position
    tokenPtr = *(int**)(thisPtr + 8);
    tokenPtr[1] = (int)(float)result; // store as float, truncate to int? Might be reinterpretation
    *tokenPtr = tokenType; // store type (1,2,3 based on last loop)
    *(int*)(thisPtr + 8) = *(int*)(thisPtr + 8) + 8; // advance current pointer
    return 1;
}

Note: The function's logic appears to read exponent and mantissa from different positions (one from limit+8, one from limit), which is unusual. Possibly this is a post-processing step after parsing, where tokens are stored in reverse order? Alternatively, the decompiled code might have incorrectly merged two similar blocks. The `tokenPtr` variable is reused and sometimes assigned from `thisPtr+0xc` directly instead of `thisPtr+0xc+8`. This could be a bug in the decompilation or a misinterpretation. However, for reconstruction we keep the structure as decompiled.

Given the complexity and potential for misinterpretation, we produce a best-effort reconstruction. We'll add comments explaining the offsets and known constants. The function likely belongs to a tokenizer class used for number evaluation in the scripting system.