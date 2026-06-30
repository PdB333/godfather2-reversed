// FUNC_NAME: CoverHintNodeManager::findBestCoverPoint
int __thiscall CoverHintNodeManager::findBestCoverPoint(CoverHintNodeManager* this, int* query, int** outNode, char allowDebug)
{
    int* nodeTable;
    int* hintData;
    int* pOVar8;
    int iVar6;
    int iVar7;
    int score;
    int* bestNode;
    byte cnt1;
    byte cnt2;
    ushort index;
    int* tempPtr;
    int** ppiVar9;
    uint loopIdx;
    float randVal;
    int local_44;
    int evalResult;
    uint mask;
    int* local_2c;
    int* local_28;
    int* local_24;
    int bestCandidate;
    int bestCandNext;
    int bestCandPrev;
    int scratch;
    int stackVar;
    
    nodeTable = (int*)*query;
    if ((nodeTable != (int*)0x0) && (hintData = (int*)query[2], hintData != (int*)0x0))
    {
        pOVar8 = *(int**)(this + 0x118);
        if (pOVar8 == (int*)0x0)
        {
            if ((allowDebug == '\0') || (evalResult = 1, (*(ushort*)(hintData + 0x18) & 0x4000) != 0))
            {
                evalResult = 0;
            }
            cnt1 = *(byte*)(hintData + 0x14);
            local_28 = (int*)0x0;
            local_24 = (int*)0x0;
            local_2c = (int*)0x0;
            local_44 = -0x7f;  // initial worst score
            loopIdx = 0;
            if (cnt1 != 0)
            {
                do
                {
                    // compute offset into hint data array (each entry 0x10 bytes)
                    index = (ushort)(*(short*)(hintData + 0x10) + (short)loopIdx);
                    iVar6 = (uint)index * 0x10 + *(int*)(nodeTable + 0x24);
                    mask = *(uint*)(this + 0x114);
                    if ((mask & (uint)*(ushort*)(iVar6 + 10)) == 0)
                    {
                        ushort uVar2 = *(ushort*)(iVar6 + 4);
                        int* basePtr = *(int**)(nodeTable + 0x20);
                        iVar7 = FUN_005fe270(evalResult);  // isValidCandidate?
                        if (iVar7 >= 0)
                        {
                            FUN_005f5c20(nodeTable, basePtr + (uint)uVar2 * 0x24);  // prepare candidate
                            score = (**(code**)(this + 0xa0))(this, query, &scratch);  // evaluate
                            if ((local_44 <= score) &&
                               ((local_44 < score ||
                                (randVal = (float)FUN_00427180(), randVal < *(float*)DAT_00e2cd54))))
                            {
                                FUN_005f7ba0(&scratch);  // store best result
                                local_44 = score;
                            }
                            FUN_005f5bb0();  // cleanup
                        }
                    }
                    loopIdx++;
                } while (loopIdx < cnt1);
            }
            if ((*(uint*)(this + 0xb4) >> 10 & 1) != 0)
            {
                bestCandidate = 0;
                bestCandNext = 0;
                bestCandPrev = 0;
                cnt2 = *(byte*)(hintData + 0x1c);
                loopIdx = 0;
                uint total = (uint)cnt2 + (uint)*(byte*)(hintData + 0x15);
                if (total != 0)
                {
                    do
                    {
                        // second array, offset 0x30 in nodeTable
                        index = (ushort)(*(short*)(hintData + 0x16) + (short)loopIdx);
                        iVar6 = (uint)index * 0x10 + *(int*)(nodeTable + 0x30);
                        if ((*(uint*)(this + 0x114) & (uint)*(ushort*)(iVar6 + 10)) == 0)
                        {
                            int* candNode = (int*)FUN_005fd1c0(&scratch, iVar6);  // get candidate node
                            if ((&bestCandidate != candNode) &&
                                (iVar6 = *candNode, bestCandidate != iVar6))
                            {
                                if (bestCandidate != 0)
                                {
                                    FUN_004daf90(&bestCandidate);  // free previous
                                }
                                bestCandidate = iVar6;
                                if (iVar6 != 0)
                                {
                                    bestCandNext = *(int*)(iVar6 + 4);
                                    *(int**)(iVar6 + 4) = &bestCandidate;
                                }
                            }
                            bestCandPrev = candNode[2];
                            // remove node from scratch list (linked list manipulation)
                            if (scratch != 0)
                            {
                                int* pListNode = *(int**)(scratch + 4);
                                if (pListNode == &scratch)
                                {
                                    *(int*)(scratch + 4) = stackVar;
                                }
                                else
                                {
                                    while ((int*)pListNode[1] != &scratch)
                                    {
                                        pListNode = (int*)pListNode[1];
                                    }
                                    pListNode[1] = stackVar;
                                }
                            }
                            // if we have a candidate and its score is better
                            if ((bestCandidate != 0) &&
                                (iVar7 = FUN_005fe270(evalResult), iVar7 >= 0) &&
                                (score = (**(code**)(this + 0xa0))(this, query, &bestCandidate),
                                local_44 <= score) &&
                                ((local_44 < score ||
                                 (randVal = (float)FUN_00427180(), randVal < *(float*)DAT_00e2cd54))))
                            {
                                FUN_005f7ba0(&bestCandidate);
                                local_44 = score;
                            }
                        }
                        loopIdx++;
                    } while (loopIdx < total);
                    // clean up linked list
                    if (bestCandidate != 0)
                    {
                        int* pNext = *(int**)(bestCandidate + 4);
                        if (pNext == &bestCandidate)
                        {
                            *(int*)(bestCandidate + 4) = bestCandNext;
                        }
                        else
                        {
                            while ((int*)pNext[1] != &bestCandidate)
                            {
                                pNext = (int*)pNext[1];
                            }
                            pNext[1] = bestCandNext;
                        }
                    }
                }
            }
            // output best result
            if (local_44 >= 0)
            {
                int* bestPtr = local_2c;
                if ((outNode != &local_2c) && (*outNode != local_2c))
                {
                    if (*outNode != (int*)0x0)
                    {
                        FUN_004daf90(outNode);
                    }
                    *outNode = bestPtr;
                    if (bestPtr != (int*)0x0)
                    {
                        outNode[1] = (int*)bestPtr[1];
                        bestPtr[1] = (int)outNode;
                    }
                }
                outNode[2] = local_24;
                if (local_2c != (int*)0x0)
                {
                    int** ppPrev = (int**)local_2c[1];
                    if (ppPrev == &local_2c)
                    {
                        local_2c[1] = (int)local_28;
                        return 1;
                    }
                    while ((int**)ppPrev[1] != &local_2c)
                    {
                        ppPrev = (int**)ppPrev[1];
                    }
                    ppPrev[1] = local_28;
                }
                return 1;
            }
            // cleanup if no best found
            if (local_2c != (int*)0x0)
            {
                int** ppPrev = (int**)local_2c[1];
                if (ppPrev == &local_2c)
                {
                    local_2c[1] = (int)local_28;
                    return 0;
                }
                while ((int**)ppPrev[1] != &local_2c)
                {
                    ppPrev = (int**)ppPrev[1];
                }
                ppPrev[1] = local_28;
                return 0;
            }
        }
        else
        {
            // alternate path: developer/debug mode using external allocator
            int count = (**(code**)(*pOVar8 + 8))();
            if (*(uint*)(this + 0x120) < (uint)(count - 1))
            {
                void* newAlloc = (**(code**)(*pOVar8 + 0xc))(*(uint*)(this + 0x120) + 1);
                FUN_005f7ba0(newAlloc);
                if ((*outNode != (int*)0x0) && (outNode[2] != (int*)0x0))
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}