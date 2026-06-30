// FUNC_NAME: ScriptVM::parseNumericLiteral
// Reconstructed from Ghidra at 0x0062d740
// Parses a numeric token (integer or float) and pushes the result onto the stack.
// Handles base conversion via strtoul and also evaluates expressions for base-10 floats.

int __thiscall ScriptVM::parseNumericLiteral(void* thisPtr) {
    int* pToken;              // iterator over token stream
    int* pCurrent;            // current stack pointer (token pointer?)
    float fBase;              // detected base from top-of-stack
    int iBase;                // integer base
    int tokenType;            // type of current token
    float fResult;            // computed numeric value
    unsigned long ulValue;    // parsed unsigned long
    char* pStr;               // pointer to string data of token
    char* endPtr;             // end pointer for strtoul
    int isBase10;             // flag

    // initial: get token from stream? +0xC points to token array, +0x8 to current token pointer?
    pToken = (int*)(*(int*)((char*)thisPtr + 0xC) + 8);   // token data start? (skip header)
    fBase = *(float*)(0x00e39f98);                       // default base? (global)

    // check if there is a token and it has a type > 0
    if ((pToken < *(int**)((char*)thisPtr + 8)) && (pToken != 0) && (*pToken > 0)) {
        // Evaluate something that returns a float (top-of-stack?) into fBase
        ScriptVM::evaluateTop(thisPtr);                  // 0x00628080
        fBase = in_XMM0_Da;                              // from XMM0 (calling convention)
    }
    iBase = (int)fBase;

    if (iBase == 10) {
        // Base 10 processing: expect numeric value
        pToken = *(int**)((char*)thisPtr + 0xC);
        pCurrent = *(int**)((char*)thisPtr + 8);
        if ((pCurrent <= pToken) || (pToken == 0) || (*pToken == -1)) {
            pToken = (int*)ScriptVM::error(thisPtr, 1, "value expected"); // 0x00627a20
            pCurrent = extraout_ECX;
        }
        if ((pToken < pCurrent) && (pToken != 0) &&
            ((*pToken == 3) || ((*pToken == 4 && (iBase = ScriptVM::isStringToken(thisPtr, (char*)local_10), iBase != 0))))) {
            // token type is number (3) or string that can be parsed (4)
            fResult = (float)ScriptVM::parseFloat(thisPtr, 1); // 0x006259b0
            pCurrent = *(int**)((char*)thisPtr + 8);
            *pCurrent = 3;                                 // token type becomes number
            goto pushFloat;
        }
        goto errorCleanup;
    }

    // Non-base 10: parse integer string using strtoul
    pStr = *(char**)((char*)thisPtr + 0xC);
    if ((pStr < *(char**)((char*)thisPtr + 8)) && (pStr != 0)) {
        int tokenType = *(int*)pStr;
        if (tokenType == 4) {
            // string token: data offset +0x10
            pStr = (char*)(*(int*)(pStr + 4) + 0x10);
        } else {
            int isToken = ScriptVM::checkTokenType(thisPtr); // 0x00633990
            if (isToken == 0) {
                pStr = 0;
            } else {
                pStr = (char*)(*(int*)(pStr + 4) + 0x10);
            }
            // check if we need to grow stack? (not important here)
            if (*(unsigned int*)(*(int*)((char*)thisPtr + 0x10) + 0x20) <= *(unsigned int*)(*(int*)((char*)thisPtr + 0x10) + 0x24)) {
                ScriptVM::growStack(thisPtr); // 0x00627360
            }
        }
        if (pStr == 0) goto getStringFallback;
    } else {
getStringFallback:
        iBase = 1;
        ScriptVM::reportError(thisPtr, "s", "string"); // 0x00627ac0 (format "string")
    }

    // Validate base: must be between 2 and 36 (0x22 = 34? but standard max 36)
    if ((unsigned int)(iBase - 2) > 0x22) {
        ScriptVM::error(thisPtr, 2, "base out of range"); // 0x00627a20
        // This generates a software interrupt (break) to debugger
        __asm { swi 3 }
        // unreachable
        return 0;
    }

    ulValue = strtoul(pStr, &endPtr, iBase);
    if (pStr != endPtr) {
        // skip trailing whitespace
        while (isspace((unsigned char)*endPtr)) {
            endPtr++;
        }
        if (*endPtr == 0) {
            pCurrent = *(int**)((char*)thisPtr + 8);
            fResult = (float)(int)ulValue;
            *pCurrent = 3;   // token type number
            if ((int)ulValue < 0) {
                // negative: adjust for unsigned conversion (float trick with 0x100000000)
                pCurrent[1] = (float)(ulValue + 0x100000000); // 0x100000000 = 4294967296.0
                *(int*)((char*)thisPtr + 8) = *(int*)((char*)thisPtr + 8) + 8;
                return 1;
            }
            // positive:
pushFloat:
            pCurrent[1] = fResult;
            *(int*)((char*)thisPtr + 8) = *(int*)((char*)thisPtr + 8) + 8;
            return 1;
        }
    }

errorCleanup:
    // Push a zero token (type 0) and advance
    **(int**)((char*)thisPtr + 8) = 0;
    *(int*)((char*)thisPtr + 8) = *(int*)((char*)thisPtr + 8) + 8;
    return 1;
}