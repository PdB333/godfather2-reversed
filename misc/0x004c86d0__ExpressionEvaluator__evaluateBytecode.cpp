// FUNC_NAME: ExpressionEvaluator::evaluateBytecode
int ExpressionEvaluator::evaluateBytecode(void* context) // context = param_1
{
    // context structure offsets:
    // +0x08: end pointer of bytecode array (int*)
    // +0x0c: start pointer of bytecode array (int*)
    // +0x10: pointer to runtime state (has +0x20 and +0x24 for capacity check)
    // +0x40: special register (int)

    int* bytecodeStart = *(int**)((char*)context + 0xc);
    int* bytecodeEnd = *(int**)((char*)context + 0x8);
    int numElements = ((int)bytecodeEnd - (int)bytecodeStart) >> 3; // each element is 8 bytes

    int resultIndex = 0;
    char* stringData = nullptr;

    // Process first element if present
    if (bytecodeStart < bytecodeEnd && bytecodeStart != nullptr) {
        if (*bytecodeStart == 4) {
            // Type 4: string data at offset +0x10 from the value
            stringData = (char*)(bytecodeStart[1] + 0x10);
        } else {
            int checkResult = FUN_00633990(context);
            if (checkResult != 0) {
                stringData = (char*)(bytecodeStart[1] + 0x10);
            } else {
                stringData = nullptr;
            }
            // Check runtime buffer capacity
            int* runtimeState = *(int**)((char*)context + 0x10);
            if (*(unsigned int*)(runtimeState + 0x20) <= *(unsigned int*)(runtimeState + 0x24)) {
                FUN_00627360(); // error handler
            }
        }
    }

    // Result array: 16 floats (8 pairs)
    float resultArray[16];
    for (int i = 0; i < 16; i++) {
        resultArray[i] = 0.0f;
    }
    int pairCount = 0;

    // Iterate over bytecode elements starting from index 2
    int currentIndex = 2;
    if (numElements > 1) {
        do {
            int* elementPtr;
            if (currentIndex < 1) {
                // Negative indices: special registers
                if (currentIndex < -9999) {
                    if (currentIndex == -0x2711) {
                        elementPtr = (int*)((char*)context + 0x40);
                    } else if (currentIndex == -10000) {
                        int* runtimeState = *(int**)((char*)context + 0x10);
                        elementPtr = (int*)((char*)runtimeState + 0x2c);
                    } else {
                        int* base = *(int**)((char*)context + 0xc);
                        int typeInfo = *(int*)((char*)base - 4);
                        int maxNeg = (int)(unsigned char)*(char*)(typeInfo + 7);
                        if (maxNeg < -0x2711 - currentIndex) {
                            elementPtr = nullptr;
                        } else {
                            elementPtr = (int*)(typeInfo + 8 + (-0x2711 - currentIndex) * 8);
                        }
                    }
                } else {
                    elementPtr = (int*)((int)bytecodeEnd + currentIndex * 8);
                }
                if (elementPtr != nullptr) {
                    goto processElement;
                }
            } else {
                elementPtr = (int*)((int)bytecodeStart - 8 + currentIndex * 8);
                if (elementPtr < bytecodeEnd) {
                    goto processElement;
                }
            }
            // If elementPtr is out of bounds, skip
            goto nextIteration;

processElement:
            if (elementPtr == nullptr) goto nextIteration;
            switch (*elementPtr) {
                case 0: {
                    // Push zero pair
                    resultArray[resultIndex * 2] = 0.0f;
                    resultArray[resultIndex * 2 + 1] = 0.0f; // flag 0
                    resultIndex++;
                    pairCount++;
                    break;
                }
                case 1: {
                    // Boolean result from function
                    float* target = &resultArray[resultIndex * 2];
                    int boolResult = FUN_00625a30(context, currentIndex);
                    *target = (float)(unsigned int)(boolResult != 0);
                    target[1] = 1.0f; // flag 1 (stored as denormalized float 4.2039e-45)
                    resultIndex++;
                    pairCount++;
                    break;
                }
                case 2:
                case 7: {
                    float value;
                    if (currentIndex < 1) {
                        int* specialPtr = (int*)FUN_00625430();
                        if (specialPtr != nullptr) {
                            if (*specialPtr == 2) {
                                value = (float)specialPtr[1];
                            } else if (*specialPtr == 7) {
                                value = (float)(specialPtr[1] + 0x10);
                            } else {
                                value = 0.0f;
                            }
                        } else {
                            value = 0.0f;
                        }
                    } else {
                        int* elem = (int*)((int)bytecodeStart - 8 + currentIndex * 8);
                        if (elem < bytecodeEnd) {
                            if (*elem == 2) {
                                value = (float)elem[1];
                            } else if (*elem == 7) {
                                value = (float)(elem[1] + 0x10);
                            } else {
                                value = 0.0f;
                            }
                        } else {
                            value = 0.0f;
                        }
                    }
                    resultArray[resultIndex * 2] = value;
                    resultArray[resultIndex * 2 + 1] = 2.0f; // flag 2 (denormalized 1.4013e-45)
                    resultIndex++;
                    pairCount++;
                    break;
                }
                case 3: {
                    // Float from function
                    float* target = &resultArray[resultIndex * 2];
                    float floatVal = (float)FUN_006259b0(context, currentIndex);
                    *target = floatVal;
                    target[1] = 3.0f; // flag 3 (denormalized 2.8026e-45)
                    resultIndex++;
                    pairCount++;
                    break;
                }
                case 4: {
                    // String-related float
                    float* target = &resultArray[resultIndex * 2];
                    float floatVal = (float)FUN_00625a70(context, currentIndex);
                    *target = floatVal;
                    target[1] = 4.0f; // flag 4 (denormalized 5.60519e-45)
                    resultIndex++;
                    pairCount++;
                    break;
                }
            }

nextIteration:
            currentIndex++;
        } while (currentIndex <= numElements);
    }

    // Process string data if present
    float* stringResult = nullptr;
    unsigned short stringFlags = 0;
    if (stringData != nullptr && *stringData != '\0') {
        unsigned int hash = FUN_004dafd0(stringData);
        FUN_00408260(&stringResult, hash);
    }

    // Setup for final processing
    void** resultList = &PTR_LAB_00e365dc; // some global list
    float* processedResult = stringResult;
    char someFlag = 0;
    FUN_00408a00(&processedResult, 0);
    FUN_00408310(&stringResult);

    int finalCount = pairCount - resultIndex; // resultIndex is the count of pairs added? Actually resultIndex increments, so pairCount == resultIndex? Wait: pairCount is incremented each time, resultIndex also. So they are equal. Then finalCount = 0. But the code does: iVar7 = local_c - iVar7; where local_c is the incremented count, iVar7 is the initial 0? Actually iVar7 is initialized to 0, then local_c is set to iVar7+1, then iVar7 = local_c. So iVar7 tracks the count. At the end, iVar7 = local_c - iVar7; which is 0. So finalCount is 0. That seems odd. Possibly the decompiler misordered. Actually looking: local_c = iVar7 + 1; then later iVar7 = local_c; So iVar7 becomes the new count. At the end, iVar7 = local_c - iVar7; would be 0. But the code also does if (iVar7 != 0) { FUN_004c8460(&local_50); } So if finalCount is 0, it doesn't call. That suggests the function returns 0 normally. But the return value is iVar7 which is 0. So the function returns 0 always? That can't be right. Let's re-examine: iVar7 is initialized to 0. Then in the loop, for each case, local_c = iVar7 + 1; then iVar7 = local_c; So iVar7 increments. At the end, iVar7 = local_c - iVar7; This would set iVar7 to 0 because local_c equals the new iVar7. So indeed the final iVar7 is 0. But the function returns iVar7. So it always returns 0. That seems like a decompilation artifact. Possibly the variable iVar7 is reused. Actually the code: local_c = iVar7 + 1; ... iVar7 = local_c; So after the loop, iVar7 holds the count. Then later: iVar7 = local_c - iVar7; This subtracts the count from itself, giving 0. But local_c is the last value? Actually local_c is set each iteration, so after the loop, local_c is the last incremented value. So iVar7 = local_c - iVar7 = 0. So the function returns 0. That might be intentional: the function returns 0 on success? Or the decompiler messed up the variable mapping. I'll keep the logic as given but note it.

    if (finalCount != 0) {
        FUN_004c8460(&resultList);
    }
    return finalCount;
}