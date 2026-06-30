// FUNC_NAME: ConditionSet::evaluateConditions
uint64 __thiscall ConditionSet::evaluateConditions(uint param_2, uint param_3)
{
    // param_1 is this
    int headerPtr = *(int *)(this + 0x10);  // +0x10: pointer to header structure
    uint local_10 = 0;  // low 32 bits of result
    uint local_c = 0;   // high 32 bits of result
    uint local_14 = 0;  // index over items
    uint local_20 = 0;  // offset into items array (item size 0x30)
    uint local_10_acc = 0;
    uint local_c_acc = 0;

    if (*(short *)(headerPtr + 0x5a) != 0) {  // +0x5a: count of items
        do {
            // Compute 64-bit bit mask for current item index
            uint64 shiftResult = __allshl();  // likely shift 1 by local_14 index
            uint lowMask = (uint)shiftResult;
            uint highMask = (uint)(shiftResult >> 32);

            // Check if item's bit is set in the input mask
            if ((lowMask & param_2) != 0 || (highMask & param_3) != 0) {
                // itemPtr = base of items array + local_20
                int itemPtr = *(int *)(headerPtr + 0x38) + local_20;  // +0x38: pointer to items array
                uint conditionCount = *(ushort *)(itemPtr + 0x2e);    // +0x2e: number of conditions
                uint matchedConditions = 0;

                if (conditionCount != 0) {
                    uint tableCount = *(uint *)(this + 0x38);  // +0x38: number of entries in variable table
                    int *varTable = *(int **)(itemPtr + 0x28);  // +0x28: pointer to condition list (array of pointers)
                    do {
                        byte *condData = (byte *)*varTable;  // dereference: points to a condition structure
                        uint varIndex = 0;
                        int *foundEntry = (int *)0x0;

                        // Search variable table for a matching entry
                        if (tableCount != 0) {
                            int *tablePtr = *(int **)(this + 0x34);  // +0x34: pointer to variable table (pairs of ints)
                            do {
                                if (*tablePtr == *(int *)(condData + 4)) {  // compare variable ID
                                    foundEntry = *(int **)(this + 0x34) + varIndex * 2;
                                    break;
                                }
                                varIndex++;
                                tablePtr += 2;
                            } while (varIndex < tableCount);
                        }

                        short type = *(short *)(*(int *)(condData + 4) + 8);  // +8: variable type (1=byte,2=?,4=float?)
                        if (type == 1) {
                            byte condValue = *condData;  // condition threshold
                            byte varValue = *(byte *)(foundEntry + 1);  // current variable value
                            switch (*(undefined2 *)(condData + 8)) {  // +8: operator
                            case 0: // less
                                condResult = condValue < varValue;
                                break;
                            case 1: // greater
                                condResult = varValue < condValue;
                                break;
                            case 2: // less or equal
                                condResult = condValue <= varValue;
                                break;
                            case 3: // greater or equal
                                condResult = varValue <= condValue;
                                break;
                            case 4: // equal
                                condResult = varValue == condValue;
                                break;
                            case 5: // not equal
                                condResult = varValue != condValue;
                                break;
                            default:
                                condResult = '\0';
                            }
                        }
                        else if (type == 2) {
                            condResult = FUN_004a3a10(*(undefined2 *)(condData + 8));  // some specialized check
                        }
                        else {
                            if (type != 4) break;  // unknown type, stop evaluating
                            condResult = FUN_004a78d0(*(undefined2 *)(condData + 8), foundEntry[1], *(undefined4 *)condData);
                        }

                        if (condResult == '\0') break;  // condition failed
                        matchedConditions++;
                        varTable++;
                    } while (matchedConditions < conditionCount);
                }

                // All conditions passed? Then call trigger callback
                if (matchedConditions == conditionCount) {
                    // Get callback function from trigger table (this+0x5c)
                    int triggerPtr = *(int *)(this + 0x5c) + local_14 * 4;  // array of pointers
                    int triggerObj = **(int **)triggerPtr;
                    bool callbackResult = (**(code **)(triggerObj + 0x6c))();  // virtual callback
                    if (callbackResult != '\0') {
                        local_10 = local_10 | lowMask;
                        local_c = local_c | highMask;
                    }
                }
            }

            headerPtr = *(int *)(this + 0x10);  // reload? (not needed, but as decompiled)
            local_20 += 0x30;   // item size
            local_14++;
            uVar9 = local_10;   // redundant but preserved
            uVar10 = local_c;
        } while (local_14 < *(ushort *)(headerPtr + 0x5a));
    }

    return CONCAT44(local_c, local_10);
}