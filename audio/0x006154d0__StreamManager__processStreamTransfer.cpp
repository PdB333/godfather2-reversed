// FUNC_NAME: StreamManager::processStreamTransfer
undefined4 __thiscall StreamManager::processStreamTransfer(uint srcHandle, uint dstHandle, int mixParam)
{
    byte bVar1;
    bool bVar2;
    bool bVar3;
    bool bVar4;
    bool bVar5;
    short sVar6;
    byte* srcInfo;
    int iVar8;
    int iVar9;
    int iVar10;
    undefined4 uVar11;
    undefined4 retainedObj;
    bool keepPrevObj;
    int prevStreamIdx;
    int local_cc;
    LARGE_INTEGER perfCounter;
    uint startLow;
    int startHigh;
    byte srcSubStreamBuf[2];
    short srcSample1;
    short srcSample2;
    undefined2 uStack_aa;
    int srcType;
    uint flags;
    int retainedSampleA;
    int retainedSampleB;
    undefined4 uStack_90;
    int local_88;
    undefined4 uStack_84;
    int local_6c;
    LARGE_INTEGER endCounter;
    int local_5c;
    undefined4 local_58;
    int local_54;
    byte dstSubStreamBuf[2];
    undefined4 dstSample1;
    int dstStreamIdx;
    uint dstFlags;
    int local_28;
    undefined4 local_24;
    int local_c;

    QueryPerformanceCounter(&perfCounter);
    startLow = perfCounter.LowPart;
    startHigh = perfCounter.HighPart;

    if (srcHandle < 0x1000) {
        srcInfo = &DAT_011a0f28 + srcHandle * 0x38;
        if (srcInfo != (byte*)0x0 && srcInfo[0] > 1) {
            bVar1 = srcInfo[1]; // subStreamCount
            if (dstHandle < 0x1000) {
                puVar7 = &DAT_011a0f28 + dstHandle * 0x38;
            } else {
                puVar7 = (byte*)0x0;
            }
            int dstSubStreamCount = puVar7[1];
            keepPrevObj = false;
            retainedObj = 0;
            prevStreamIdx = 0;
            local_cc = 0;

            if (dstSubStreamCount != 0) {
                do {
                    int curStreamIdx = prevStreamIdx;
                    undefined4 curRetainedObj = retainedObj;
                    int readResult = readStreamData(dstHandle, 10, local_cc, srcSubStreamBuf);
                    if (readResult == 0) {
                        return 0;
                    }
                    int maxSubStream = bVar1 - 1;
                    int subStreamIdx = local_cc;
                    if ((local_cc < maxSubStream) || (subStreamIdx = maxSubStream, local_cc <= maxSubStream)) {
                        if (keepPrevObj) {
                            releaseObject(curRetainedObj, 0);
                            retainedObj = 0;
                            keepPrevObj = false;
                        }
                        readResult = readStreamData(srcHandle, 9, subStreamIdx, dstSubStreamBuf);
                        if (readResult == 0) {
                            releaseBuffer(srcSubStreamBuf);
                            return 0;
                        }
                        curRetainedObj = local_c;
                        int newStreamIdx = local_28;
                        bool bTemp2 = false;
                        bool bTemp4 = keepPrevObj;
                    } else {
                        readResult = readStreamData(dstHandle, 9, local_cc - 1, dstSubStreamBuf);
                        if (readResult == 0) {
                            releaseBuffer(srcSubStreamBuf);
                            return 0;
                        }
                        dstFlags = local_24 & 0xFFFFFFEF;
                        dstStreamIdx = 3;
                        retainedObj = 0;
                        prevStreamIdx = 0;
                        bTemp4 = false;
                        bTemp2 = keepPrevObj;
                    }
                    uVar11 = curRetainedObj;
                    if ((dstFlags & 0x10) != 0) {
                        local_5c = 2;
                        local_58 = 0x10;
                        local_54 = 0;
                        uVar11 = allocateObject(local_24, &local_5c);
                        if (bTemp2) {
                            releaseObject(curRetainedObj, 0);
                        }
                        bTemp2 = true;
                        newStreamIdx = local_28;
                    }
                    sVar6 = srcSample1;
                    if (dstSample1 != srcSample1 || uStack_aa != srcSample2) {
                        if (srcType == 0x1e || srcType == 0x1f || srcType == 0x20 || srcType == 0x21 || srcType == 0x22 || srcType == 0x23) {
                            local_88 = decodeFrequency(srcSample1);
                            curRetainedObj = decodeFrequency(sVar6);
                        } else {
                            local_88 = local_88;
                            curRetainedObj = uStack_84;
                        }
                        curRetainedObj = retainObject(curRetainedObj);
                        if ((dstStreamIdx == 3 || dstStreamIdx == 2) && mixParam != 0) {
                            mixAudioChunk(curRetainedObj, CONCAT22(srcSample2, srcSample1), CONCAT22(uStack_aa, srcSample2), uVar11, dstSample1, newStreamIdx, mixParam);
                        }
                        if (bTemp2) {
                            releaseObject(uVar11, 0);
                        }
                        bTemp2 = true;
                        newStreamIdx = local_88;
                    }
                    int currentType = srcType;
                    bool useNewObj = true;
                    bool bTemp3 = bTemp2;
                    keepPrevObj = bTemp4;
                    if ((int)(uint)bVar1 < dstSubStreamCount) {
                        bTemp3 = false;
                        retainedObj = curRetainedObj;
                        prevStreamIdx = newStreamIdx;
                        keepPrevObj = bTemp2;
                    }
                    local_88 = curRetainedObj;
                    bStack_d5 = bTemp3;
                    if ((srcType != dstStreamIdx) &&
                        ((srcType >= 0x1e && srcType <= 0x23)) &&
                        ((dstStreamIdx < 0x1e || dstStreamIdx > 0x23))) {
                        bStack_d5 = (dstFlags & 0x10) == 0;
                        if (bStack_d5) {
                            local_88 = local_6c;
                        } else {
                            local_88 = retainObject(uStack_84);
                        }
                        bStack_d5 = !bStack_d5;
                        commitOutput(local_88, local_88, currentType, curRetainedObj, newStreamIdx, CONCAT22(srcSample2, srcSample1), CONCAT22(uStack_aa, srcSample2));
                        newStreamIdx = local_88;
                        useNewObj = bStack_d5;
                        if (bTemp3) {
                            releaseObject(curRetainedObj, 0);
                            newStreamIdx = local_88;
                        }
                    }
                    if ((dstFlags & 0x10) == 0) {
                        if (useNewObj) {
                            finalizeTransfer(local_6c, local_88, newStreamIdx, uStack_90);
                        }
                        retainedObj = local_88;
                        if (!bStack_d5) goto LAB_0061540a;
                    } else {
                        if (newStreamIdx == local_88) goto LAB_00615403;
                        retainedObj = retainObject(uStack_84);
                        finalizeTransfer(retainedObj, local_88, newStreamIdx, uStack_90);
                        if (bStack_d5) {
                            releaseObject(local_88, 0);
                        }
LAB_0061540a:
                        releaseObject(retainedObj, 0);
                    }
                    releaseBuffer(dstSubStreamBuf);
                    releaseBuffer(srcSubStreamBuf);
                    local_cc = local_cc + 1;
                } while (local_cc < dstSubStreamCount);
                if (keepPrevObj) {
                    releaseObject(retainedObj, 0);
                }
            }
            QueryPerformanceCounter(&endCounter);
            bool carry = __CFADD__(_DAT_01205940, endCounter.LowPart - startLow);
            _DAT_01205940 += endCounter.LowPart - startLow;
            _DAT_01205944 += (endCounter.HighPart - startHigh) - (uint)(endCounter.LowPart < startLow) + (uint)carry;
            return 1;
        }
    }
    return 0;
}