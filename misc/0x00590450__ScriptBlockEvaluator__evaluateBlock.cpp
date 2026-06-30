// FUNC_NAME: ScriptBlockEvaluator::evaluateBlock
float __thiscall ScriptBlockEvaluator::evaluateBlock(int this, void* commandBlock, float* curveData)
{
    int commandCount = (signed char)(*(char*)commandBlock + 1);  // +1 byte from start
    float accumulator = 0.0f;
    float sum = 0.0f;

    if (commandCount == 0)
        return 1.0f;

    if (commandCount > 0)
    {
        char** commandPtrs = (char**)((char*)commandBlock + 12);  // array of pointers at offset 0xC
        for (int i = 0; i < commandCount; i++)
        {
            char* token = commandPtrs[i];
            if (token[0] == '\t')  // tab command
            {
                uint id = *(uint*)(*(int*)(token + 4) + 4);  // double indirection: token+4 is int pointer, then +4 for id
                if ((uint)curveData[1] <= id)  // compare with curveData[1] (maybe size)
                {
                    int errorCode = 0;
                    logAssert(&errorCode);  // FUN_00591c00
                }
                float curveValue = *(curveData + id);  // read float from curve array at index id
                if (curveValue != SENTINEL_VALUE)   // DAT_00e2b04c is a sentinel constant (likely -1.0f or NaN)
                {
                    nextCommand();   // FUN_00591160
                    curveValue += sum;
                    sum = curveValue;
                }
                else
                {
                    nextCommand();   // FUN_00591160
                }
            }
            else  // non-tab command
            {
                // Normal command path: accumulate directly
                nextCommand();   // FUN_00591160
                curveValue += sum;   // Actually in code: fVar3 = fVar3 + local_c; local_c = fVar3;
                // But fVar3 was undefined if not tab? In the else branch, fVar3 is not set from curve array.
                // Correction: In the original else (non-tab) path, it jumps to LAB_005904d8 which does:
                // FUN_00591160(); fVar3 = fVar3 + local_c; local_c = fVar3;
                // But fVar3 is not initialized from curve in this path. So likely fVar3 retains previous value.
                // For non-tab, we should still accumulate previous fVar3.
                // So we need a variable to track the "current value" that carries across iterations.
                // In the decompiled, fVar3 is declared outside loop and only set in tab case.
                // For non-tab, it accumulates using the previous fVar3 (which might be from previous tab or zero).
                // So we need to keep fVar3 across iterations.
                // But in our pseudo-code we used accumulator for this? Let's reconstruct more carefully.
                // Actually original code:
                // fVar3 = 0.0; local_c = 0.0;
                // if (local_8==0) return 1;
                // if (local_8>0) {
                //   do {
                //      if (*puVar2[0]=='\t') {
                //         uVar1 = ...; if (param_3[1] <= uVar1) ...
                //         fVar3 = *(float*)(*param_3 + uVar1*4);
                //         if (fVar3 != DAT) goto LAB_005904d8;
                //         FUN_00591160();
                //      } else {
                // LAB_005904d8:
                //         FUN_00591160();
                //         fVar3 = fVar3 + local_c;
                //         local_c = fVar3;
                //      }
                //   } while (--local_8 != 0);
                // }
                // return local_c;
                // So for non-tab, it goes to LAB_005904d8 where it calls FUN_00591160 and then fVar3 = fVar3 + local_c; local_c = fVar3.
                // For tab, if fVar3!=DAT, it also goes to the same block (but the block is after the if, not in the else).
                // So the only difference is that for tab, first it reads fVar3 from curve and checks, then if not sentinel, it goes to the same accumulation block. If sentinel, it just calls FUN_00591160 and skips accumulation (the block ends with return? Actually code after LAB_005904d8 continues? In the decompiled, the block for tab if not sentinel ends with goto LAB_005904d8, which is in the else? Actually the if branch for tab: if (fVar3 != DAT) goto LAB_005904d8; then after that (if equal) it calls FUN_00591160 and then implicitly falls through? The decompiled shows:
                // if (fVar3 != DAT_00e2b04c) goto LAB_005904d8;
                // FUN_00591160();
                // then after that? The code shows that after the tab's if block, the loop continues? Actually the decompiled shows that after the if inside tab, there is no explicit code after FUN_00591160(); but the loop continues to the next iteration. So for tab when fVar3==DAT, it calls nextCommand and then continues to next iteration without accumulating. So the accumulation block is only executed in non-tab path and in tab path when fVar3!=DAT. So we need to restructure.
                // Better: For each command:
                //   if token is tab and read curve value
                //   if curve value is sentinel, just call nextCommand and continue (no accumulate)
                //   else: call nextCommand, then fVar3 = fVar3 + sum; set sum = fVar3;
                // For non-tab: same as else part: call nextCommand, then fVar3 = fVar3 + sum; set sum = fVar3.
                // So the accumulation happens for both non-tab and tab (if not sentinel). The only difference is that for non-tab, fVar3 is not updated from curve (keeps previous fVar3). So fVar3 carries across commands.
                // Thus we need a variable current_value that persists across loop iterations.
            }
        }
    }
    return sum;
}