// FUNC_NAME: PatternMatcher::match
int PatternMatcher::match(void) // __thiscall? Actually no explicit this, but param_1 is pointer to context
{
    char cVar1;
    undefined4 *outputToken;
    int iVar3;
    int iVar4;
    char *patternStr;
    int *tokenPtr;
    uint uVar7;
    float in_XMM0_Da;
    float fVar8;
    int stackVar_128;
    uint matchLen;
    int startOffset;
    char *matchedStr;
    int stackVar_118;
    uint maxPos;
    int stackVar_110;
    undefined4 stackVar_10c;

    // Current token pointer in input stream
    tokenPtr = *(int **)(this + 0xc);
    // Check if token ptr is valid (within buffer bounds)
    if ((tokenPtr < *(int **)(this + 8)) && (tokenPtr != (int *)0x0)) {
        if (*tokenPtr == 4) {
            // Token type 4: direct offset from stored value +0x10
            startOffset = tokenPtr[1] + 0x10;
        } else {
            iVar4 = FUN_00633990(this);
            if (iVar4 == 0) {
                startOffset = 0;
            } else {
                startOffset = tokenPtr[1] + 0x10;
            }
            // Check for buffer overflow? Advance read pointer?
            if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24)) {
                FUN_00627360();
            }
        }
        if (startOffset == 0) goto LAB_0062c330;
    } else {
LAB_0062c330:
        // Error: invalid token, print string
        FUN_00627ac0(PTR_s_string_00e2a8ac);
    }

    // Read match length from next token
    tokenPtr = *(int **)(this + 0xc);
    if ((tokenPtr < *(int **)(this + 8)) && (tokenPtr != (int *)0x0)) {
        if (*tokenPtr == 4) {
            matchLen = *(uint *)(tokenPtr[1] + 0xc);
        } else {
            iVar4 = FUN_00633990(this);
            if (iVar4 == 0) {
                matchLen = 0;
            } else {
                matchLen = *(uint *)(tokenPtr[1] + 0xc);
            }
        }
    } else {
        matchLen = 0;
    }

    // Read pattern string from third token (offset +8 from current position)
    iVar4 = *(int *)(this + 0xc);
    tokenPtr = (int *)(iVar4 + 8);
    if ((tokenPtr < *(int **)(this + 8)) && (tokenPtr != (int *)0x0)) {
        if (*tokenPtr == 4) {
            matchedStr = (char *)(*(int *)(iVar4 + 0xc) + 0x10);
        } else {
            iVar3 = FUN_00633990(this);
            if (iVar3 == 0) {
                matchedStr = (char *)0x0;
            } else {
                matchedStr = (char *)(*(int *)(iVar4 + 0xc) + 0x10);
            }
            if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24)) {
                FUN_00627360();
            }
        }
        if (matchedStr != (char *)0x0) goto LAB_0062c3e3;
    }
    // If invalid, set pattern to a dummy value (0x2)
    matchedStr = (char *)0x2;
    FUN_00627ac0(PTR_s_string_00e2a8ac);
LAB_0062c3e3:

    // Read capture offset from fourth token (offset +8 from current? actually +8 from base)
    iVar4 = *(int *)(this + 0xc);
    tokenPtr = (int *)(iVar4 + 8); // same as before? Actually this reads token at iVar4+8 again, but should be next token (offset +16?)
    // Wait, note: the code reads token at base+0xc, then later base+0xc+8, then here base+0xc+8? That seems off. 
    // Let's trace: after reading pattern, the code reads again from same position? Might be a bug in decompilation.
    // Actually, the code reads iVar4 = this+0xc, then tokenPtr = iVar4+8. But after reading pattern, the stream may have advanced.
    // Here it re-reads the same token? I think it's reading the next token which is at the new current position.
    // I'll assume it's reading a fourth token (offset +0x10 from base? Maybe the variable iVar4 is reused).
    // Actually looking at the code: it uses iVar4 from earlier (the current position) but that position has advanced after reading pattern.
    // So it's reading the next token in the stream. I'll name it captureToken.
    if ((tokenPtr < *(int **)(this + 8)) && (tokenPtr != (int *)0x0)) {
        if (*tokenPtr == 4) {
            stackVar_128 = *(int *)(*(int *)(iVar4 + 0xc) + 0xc);
        } else {
            iVar3 = FUN_00633990(this);
            if (iVar3 == 0) {
                stackVar_128 = 0;
            } else {
                stackVar_128 = *(int *)(*(int *)(iVar4 + 0xc) + 0xc);
            }
        }
    } else {
        stackVar_128 = 0;
    }

    // Read a float from token at offset +0x10 from current (offset +0x10 from base+0xc)
    tokenPtr = (int *)(*(int *)(this + 0xc) + 0x10);
    fVar8 = DAT_00e2b1a4;
    if (((tokenPtr < *(int **)(this + 8)) && (tokenPtr != (int *)0x0)) && (0 < *tokenPtr)) {
        FUN_00628080();
        fVar8 = in_XMM0_Da;
    }

    // Calculate search range
    iVar4 = (int)fVar8; // fVar8 is a float, truncate to int? May be a count or offset
    if (iVar4 < 0) {
        iVar4 = matchLen + 1 + iVar4; // negative means from end?
    }
    uVar7 = iVar4 - 1; // This will be the end position (or start?)
    if ((int)uVar7 < 0) {
        uVar7 = 0;
    } else if (matchLen < uVar7) {
        uVar7 = matchLen;
    }

    // Check if pattern contains regex special characters, or if flags indicate simple pattern
    tokenPtr = (int *)(*(int *)(this + 0xc) + 0x18); // Another token? At offset +0x18 from current
    if ((((tokenPtr < *(int **)(this + 8)) && (tokenPtr != (int *)0x0)) &&
        ((*tokenPtr != 0 && ((*tokenPtr != 1 || (*(int *)(*(int *)(this + 0xc) + 0x1c) != 0)))))) ||
       (patternStr = _strpbrk(matchedStr, "^$*+?.([%-\"), patternStr == (char *)0x0)) {
        // Simple literal match (no regex special chars)
        iVar4 = FUN_0062c050(startOffset + uVar7, matchLen - uVar7, matchedStr, stackVar_128);
        if (iVar4 != 0) {
            // Success: write result tokens (type 3 = float)
            outputToken = *(undefined4 **)(this + 8);
            *outputToken = 3;
            outputToken[1] = (float)((iVar4 - startOffset) + 1); // Length of match?
            *(int *)(this + 8) = *(int *)(this + 8) + 8;
            outputToken = *(undefined4 **)(this + 8);
            stackVar_128 = (iVar4 - startOffset) + stackVar_128; // Add capture offset
            fVar8 = (float)stackVar_128;
            *outputToken = 3;
            if (stackVar_128 < 0) {
                fVar8 = fVar8 + DAT_00e44578; // Adjust negative zero?
            }
            outputToken[1] = fVar8;
            *(int *)(this + 8) = *(int *)(this + 8) + 8;
            return 2; // Exact match found
        }
    } else {
        // Regex pattern: iterate over possible positions
        cVar1 = *matchedStr;
        if (cVar1 == '^') {
            matchedStr = matchedStr + 1; // Anchor at start
        }
        maxPos = matchLen + startOffset; // End of search range
        stackVar_110 = (int)this;
        stackVar_118 = startOffset;
        uVar7 = uVar7 + startOffset; // Actual start position in string
        do {
            stackVar_10c = 0;
            iVar4 = FUN_0062bd60(&stackVar_118, uVar7, matchedStr); // Try match at position
            if (iVar4 != 0) {
                // Match found at position
                outputToken = *(undefined4 **)(this + 8);
                *outputToken = 3;
                outputToken[1] = (float)(int)((uVar7 - startOffset) + 1); // Match length?
                *(int *)(this + 8) = *(int *)(this + 8) + 8;
                outputToken = *(undefined4 **)(this + 8);
                *outputToken = 3;
                outputToken[1] = (float)(iVar4 - startOffset); // Captured position?
                *(int *)(this + 8) = *(int *)(this + 8) + 8;
                iVar4 = FUN_0062c1b0(0,0); // Handle groups/captures
                return iVar4 + 2; // Return match result code
            }
            uVar7 = uVar7 + 1;
        } while ((uVar7 < maxPos) && (cVar1 != '^')); // Continue until end or anchored
    }

    // No match found: write failure token
    **(undefined4 **)(this + 8) = 0; // Type 0? Or just zero?
    *(int *)(this + 8) = *(int *)(this + 8) + 8;
    return 1; // No match
}