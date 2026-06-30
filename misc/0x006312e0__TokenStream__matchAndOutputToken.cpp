// FUNC_NAME: TokenStream::matchAndOutputToken
int __thiscall TokenStream::matchAndOutputToken(TokenStream* this) {
    int* piVar1; // pointer to current token in stream
    int typeResult; // will be 3, 2, or 1
    float floatTemp;
    int intTemp;
    float valueTemp;

    // piVar1 points one token past the logical end (based on end pointer + 8 bytes)
    piVar1 = (int*)(*(int*)(this + 0xc) + 8);
    typeResult = 3;

    // If current write position (at +0x8) is already past that sentinel, skip ahead
    if (*(int**)(this + 0x8) <= piVar1) goto LAB_006313a0;

    // Check if the sentinel is valid and its type
    if (piVar1 == (int*)0x0) goto LAB_006313a0;
    if (*piVar1 != 3) {
        // Type is not 3; if it's 4, try to convert
        if (*piVar1 != 4) goto LAB_006313a0;
        int result = FUN_00636850(&valueTemp); // attempt conversion from unknown format
        if (result == 0) goto LAB_006313a0;
        intTemp = 3;
        piVar1 = &intTemp; // point to a local temporary token
    }

    // Extract the floating-point value from the current token
    valueTemp = (float)piVar1[1];
    if (valueTemp == DAT_00e2b05c) { // compare to expected constant
        // Successful match: now look for the next token(s) to confirm pattern
        while (1) {
            piVar1 = (int*)(*(int*)(this + 0xc) + 8); // refresh sentinel pointer
            if (*(int**)(this + 0x8) <= piVar1 || piVar1 == (int*)0x0) {
                // No more tokens, set default fallback
                typeResult = 2;
                FUN_00627ac0("number"); // print warning
                goto LAB_006313a0;
            }
            // Check type: must be same as current typeResult (starting 3), or 4 with conversion
            if (*piVar1 != typeResult && (*piVar1 != 4 || (int result = FUN_00636850(&floatTemp), result == 0))) {
                // Type mismatch, try next possible type (2 then 1)
                typeResult = 2;
                FUN_00627ac0("number");
                continue;
            }
            // Matching token found, break out
            break;
        }
    }

    // At this point we have a valid matching token from the stream
    // Now write the matched token to the output buffer (at +0x8)
    piVar1 = *(int**)(this + 0x8);
    if (*(int**)(this + 0x8) <= piVar1) goto LAB_00631451;
    if (piVar1 == (int*)0x0) goto LAB_00631451;
    if (*piVar1 != typeResult) {
        if (*piVar1 != 4) goto LAB_00631451;
        int result = FUN_00636850(&floatTemp);
        if (result == 0) goto LAB_00631451;
        floatTemp = floatTemp; // already assigned
        piVar1 = &intTemp;
        intTemp = typeResult;
    }

    // Write the value (converted back to float, then stored as int)
    floatTemp = (float)piVar1[1];
    if (floatTemp == DAT_00e2b05c) {
        while (1) {
            piVar1 = *(int**)(this + 0xc);
            if (*(int**)(this + 0x8) <= piVar1 || piVar1 == (int*)0x0) {
                typeResult = 1;
                FUN_00627ac0("number");
                goto LAB_00631451;
            }
            if (*piVar1 != typeResult && (*piVar1 != 4 || (int result = FUN_00636850(&intTemp), result == 0))) {
                typeResult = 1;
                FUN_00627ac0("number");
                continue;
            }
            break;
        }
    }

    // Write final type and value to output buffer
    piVar1 = *(int**)(this + 0x8);
    *piVar1 = typeResult;
    // Call a function (possibly rounding or storing float bits)
    FUN_00b9a9fa();
    piVar1[1] = (int)(float)floatTemp; // store as int (float bits or converted)
    // Advance output pointer by one token (8 bytes)
    *(int*)(this + 0x8) = *(int*)(this + 0x8) + 8;
    return 1;

LAB_006313a0:
    // Fallback path: set value to 0 and look for any token of the required type (3,2,1)
    valueTemp = 0.0f;
    while (1) {
        piVar1 = (int*)(*(int*)(this + 0xc) + 8);
        if (*(int**)(this + 0x8) <= piVar1 || piVar1 == (int*)0x0) {
            typeResult = 2;
            FUN_00627ac0("number");
            continue;
        }
        if (*piVar1 != typeResult && (*piVar1 != 4 || (int result = FUN_00636850(&floatTemp), result == 0))) {
            typeResult = 2;
            FUN_00627ac0("number");
            continue;
        }
        break;
    }
    // ... (assume similar writing code as above but with valueTemp=0)
    // This path may be unreachable due to the goto structure; included for completeness
    // Fall through to LAB_00631451-style writing with valueTemp=0.

LAB_00631451:
    // Write fallback token with value 0
    valueTemp = 0.0f;
    while (1) {
        piVar1 = *(int**)(this + 0xc);
        if (*(int**)(this + 0x8) <= piVar1 || piVar1 == (int*)0x0) {
            typeResult = 1;
            FUN_00627ac0("number");
            continue;
        }
        if (*piVar1 != typeResult && (*piVar1 != 4 || (int result = FUN_00636850(&intTemp), result == 0))) {
            typeResult = 1;
            FUN_00627ac0("number");
            continue;
        }
        break;
    }
    // Write typeResult and value (valueTemp=0) to output
    piVar1 = *(int**)(this + 0x8);
    *piVar1 = typeResult;
    FUN_00b9a9fa();
    piVar1[1] = (int)(float)valueTemp;
    *(int*)(this + 0x8) = *(int*)(this + 0x8) + 8;
    return 1;
}