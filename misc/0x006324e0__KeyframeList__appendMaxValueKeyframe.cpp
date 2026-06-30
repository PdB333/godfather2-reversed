// FUNC_NAME: KeyframeList::appendMaxValueKeyframe
// Function at 0x006324e0: Appends a new keyframe (type=3) with the maximum value among existing keyframes.
// Processes an array of 8-byte entries: [type (int), value (float)].
// Handles special cases for type 4 (linear key) and missing values (float == 0.0f).

int KeyframeList::appendMaxValueKeyframe(int thisPtr)
{
    float* pKeyStart;
    int   keyCount;
    int*  pCurrentKey;
    int   iVar2;
    int   iVar4;
    float10 fVar5;
    float localValue;    // temporary float for evaluation
    int   localType;     // temporary type (3)
    float localFloat;    // temporary float value
    int   localNegIndex; // local for negative index logic
    float localNegFloat; // value corresponding to negative index

    pCurrentKey = *(int**)(thisPtr + 0xc);             // +0x0c: pointer to first key
    keyCount = (int)*(int**)(thisPtr + 8) - (int)pCurrentKey >> 3; // +0x08: pointer past last key

    if (*(int**)(thisPtr + 8) <= pCurrentKey) {
        goto CHECK_END;
    }
    if (pCurrentKey == (int*)0x0) {
        goto CHECK_END;
    }

    // Evaluate first key's type
    if (*pCurrentKey != 3) {
        if (*pCurrentKey != 4) {
            goto CHECK_END;
        }
        // Type 4: attempt to evaluate the key into localValue
        iVar2 = evaluateKeyFrame(thisPtr, &localValue); // FUN_00636850: evaluates type 4 key
        if (iVar2 == 0) {
            goto CHECK_END;
        }
        // Create a synthetic key (type 3) with the evaluated value
        localType = 3;
        localFloat = localValue;
        pCurrentKey = &localType; // point to local synthetic key
    }

    localValue = (float)pCurrentKey[1]; // value of the key (original or synthetic)
    if (localValue == DAT_00e2b05c) {   // sentinel value (e.g., "not set")
        // Loop until a valid key is found or error
        do {
            pCurrentKey = *(int**)(thisPtr + 0xc);
            if ((*(int**)(thisPtr + 8) <= pCurrentKey) || (pCurrentKey == (int*)0x0)) {
                debugPrint("number"); // FUN_00627ac0: error message (string "number")
                goto CHECK_END;
            }
            if ((*pCurrentKey == 3) || 
                ((*pCurrentKey == 4 && (iVar2 = evaluateKeyFrame(thisPtr, &localFloat), iVar2 != 0)))) {
                break;
            }
            debugPrint("number"); // again, probably logs an error
CHECK_END:
            localValue = 0.0f;
        } while (true);
    }

    // Iterate over remaining keys (starting from index 2) to find the maximum value
    if (1 < keyCount) {
        iVar2 = 2;
        do {
            fVar5 = (float10)getKeyframeValue(thisPtr, iVar2); // FUN_006259b0: returns float for key index
            localFloat = (float)fVar5;
            if (fVar5 == (float10)0.0f) {
                // Value is zero (likely missing key) - try to find a valid key backward
                if (iVar2 < 1) {
                    goto NEXT_INDEX;
                }
                pCurrentKey = (int*)(*(int*)(thisPtr + 0xc) + -8 + iVar2 * 8);
                if (pCurrentKey < *(int**)(thisPtr + 8)) {
                    goto SEARCH_VALID_KEY;
                }
                do {
                    debugPrint("number");
NEXT_INDEX:
                    if (iVar2 < -9999) {
                        if (iVar2 == -0x2711) {                // -10001
                            pCurrentKey = (int*)(thisPtr + 0x40);
                        }
                        else if (iVar2 == -10000) {
                            pCurrentKey = (int*)(*(int*)(thisPtr + 0x10) + 0x2c);
                        }
                        else {
                            iVar4 = *(int*)(*(int*)(thisPtr + 0xc) + -4);
                            if ((int)(uint)*(byte*)(iVar4 + 7) < -0x2711 - iVar2) {
                                pCurrentKey = (int*)0x0;
                            }
                            else {
                                pCurrentKey = (int*)(iVar4 + 8 + (-0x2711 - iVar2) * 8);
                            }
                        }
                    }
                    else {
                        pCurrentKey = (int*)(*(int*)(thisPtr + 8) + iVar2 * 8);
                    }
SEARCH_VALID_KEY:
                } while ((pCurrentKey == (int*)0x0) ||
                         ((*pCurrentKey != 3 && 
                          ((*pCurrentKey != 4 || (iVar4 = evaluateKeyFrame(thisPtr, &localFloat), iVar4 == 0))))));
            }
            if (localValue < localFloat) {
                localValue = localFloat;
            }
            iVar2 = iVar2 + 1;
        } while (iVar2 <= keyCount);
    }

    // Append new keyframe (type=3) with the maximum value found
    *(int**)(thisPtr + 8)->field0 = 3;
    *(int**)(thisPtr + 8)->field1 = localValue;
    *(int*)(thisPtr + 8) = *(int*)(thisPtr + 8) + 8; // advance end pointer
    return 1;
}