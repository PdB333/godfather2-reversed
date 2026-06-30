// FUNC_NAME: EARS::ScriptEngine::executeSetAction
undefined4 __thiscall EARS::ScriptEngine::executeSetAction(int thisPtr, float* symbolInfo, undefined4* resultPtr, undefined4 arg4, undefined4 arg5, undefined4 arg6, undefined4 arg7) {
    undefined4* tempPtr;
    short indexShort;
    int* hashTablePtr;
    uint* bucketPtr;
    uint hashValue;
    int loopCount;
    byte* opcodePtr;
    int var_i;
    uint stackSize;
    undefined4 operationResult;
    float10 evalResult;
    undefined4 local_18;
    int stackBuffer;
    uint local_10;
    int* piStack_c;
    int* local_4;

    // Initialization: get current stack context (stackBuffer, local_10)
    getScriptStackContext();

    // Ensure stack capacity at least 0x100
    if (local_10 < 0x100) {
        local_18 = 0;
        resizeScriptStack(&local_18);
    }

    // Store result pointer at offset 0x3fc in the stack buffer
    *(undefined4**)(stackBuffer + 0x3fc) = resultPtr;

    // Parse arguments from symbol info: arguments start at symbolInfo+0xc, count at symbolInfo+1
    loopCount = 0;
    if (*(char*)((int)symbolInfo + 1) > '\0') {
        resultPtr = (undefined4*)((int)symbolInfo + 0xc);
        do {
            hashValue = 0xfe - loopCount;
            if ((local_10 <= hashValue) && (var_i = (hashValue - local_10) + 1, var_i != 0)) {
                // Expand stack to accommodate further arguments
                resizeScriptStack(local_10 + var_i);
                stackSize = var_i + local_10;
                do {
                    tempPtr = (undefined4*)(stackBuffer + local_10 * 4);
                    local_10 = local_10 + 1;
                    if (tempPtr != (undefined4*)0x0) {
                        *tempPtr = 0;
                    }
                } while (stackSize != local_10);
            }
            // Copy argument onto stack (index from 0xfe down)
            operationResult = *resultPtr;
            resultPtr = resultPtr + 1;
            *(undefined4*)(stackBuffer + hashValue * 4) = operationResult;
            loopCount = loopCount + 1;
        } while (loopCount < *(char*)((int)symbolInfo + 1));
    }

    // Hash table lookup: base at this+0x70, then +0x30 for bucket array
    hashTablePtr = *(int**)(*(int*)(thisPtr + 0x70) + 0x30);
    // Hash from symbolInfo+4 modulo table size
    bucketPtr = *(uint**)(*hashTablePtr + (**(uint**)((int)symbolInfo + 4) % (uint)hashTablePtr[1]) * 4);

    do {
        if (bucketPtr == (uint*)0x0) {
            goto LAB_0059008f;
        }
        if (*bucketPtr == **(uint**)((int)symbolInfo + 4)) {
            if ((bucketPtr != (uint*)0x0) && (bucketPtr != (uint*)0xfffffffc)) {
                opcodePtr = (byte*)bucketPtr[2];
                goto found_entry;
            }
            goto LAB_0059008f;
        }
        bucketPtr = (uint*)bucketPtr[3];
    } while (true);

LAB_0059008f:
    opcodePtr = (byte*)0x0;

found_entry:
    // Default value for evaluation
    operationResult = 0x0;
    if (opcodePtr != (byte*)0x0) {
        symbolInfo = (float*)DAT_00e2b1a4;  // global default float value
        if ((*opcodePtr & 0x3f) < 0x23) {
            // Call the evaluation function for this opcode
            evalResult = (float10)(**(code**)(&DAT_0103b050 + (*opcodePtr & 0x3f) * 4))(thisPtr, opcodePtr, &stackBuffer);
            symbolInfo = (float*)(float)evalResult;
        }
        indexShort = *(short*)(opcodePtr + 2);
        if (local_10 <= (uint)(int)indexShort) {
            resultPtr = (undefined4*)0x0;
            resizeScriptStack(&resultPtr);
        }
        // Store evaluated value at stack[index]
        *(float*)(stackBuffer + indexShort * 4) = (float)symbolInfo;

        if ((*opcodePtr & 0x3f) < 0x23) {
            // Call the apply/commit function for this opcode
            operationResult = (**(code**)(&DAT_0103afc0 + (*opcodePtr & 0x3f) * 4))(thisPtr, opcodePtr, &stackBuffer, arg4, arg5, arg6, arg7);
        } else {
            operationResult = 0;
        }
    }

    // Cleanup: call virtual destructors on stack context
    (**(code**)(*local_4 + 4))(stackBuffer, 0);  // possibly finalize stackBuffer
    if (local_10 != 0) {
        (**(code**)(*piStack_c + 4))(local_10, 0);  // finalize stack size
    }
    (**(code**)(*piStack_c + 0xc))();  // release/free?
    return operationResult;
}