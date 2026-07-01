// FUNC_NAME: ProbeManager::updateProbes
void __thiscall ProbeManager::updateProbes(void* thisPtr, float* cameraTransform)
{
    char byteFlag;
    float floatVal;
    uint probeIndex;
    float* pfSource;
    int iVar5;
    int iVar6;
    uint* puVar7;
    uint* puVar8;
    int* piVar9;
    float* pfVar10;
    bool bVar11;
    bool bVar12;
    float diffX;
    float diffY;
    float diffZ;
    float distanceSq;
    float computedWeight;
    uint* probeData;
    uint local_bc;
    uint* local_b8;
    uint* local_b4[7];
    int local_98[32];
    int local_18;

    if (*(char*)(thisPtr + 0x280) == '\0') {
        probeIndex = (uint)*(byte*)(thisPtr + 0xcc);
        if (((*(int*)(thisPtr + 0xb0 + probeIndex * 4) != 0) &&
            ((*(byte*)(*(int*)(thisPtr + 0xb0 + probeIndex * 4) + 0x83) & 1) != 0)) &&
            (*(char*)(probeIndex + 0xbc + thisPtr) != '\0')) {
            FUN_0088a7b0();
            return;
        }
        if (DAT_0112e241 == '\0') {
            pfSource = cameraTransform;
            pfVar10 = (float*)(thisPtr + 0xd0);
            for (iVar6 = 0x1c; iVar6 != 0; iVar6 = iVar6 + -1) {
                *pfVar10 = *pfSource;
                pfSource = pfSource + 1;
                pfVar10 = pfVar10 + 1;
            }
            *(undefined4*)(thisPtr + 0x1c0) = 0;
            if (DAT_00e54265 == '\0') {
                local_18 = 0;
                FUN_00887f70(local_98, (float*)(thisPtr + 0xd0));
                probeIndex = 0;
                *(int*)(thisPtr + 0x1d8) = local_18;
                if (local_18 != 0) {
                    puVar7 = (undefined4*)(thisPtr + 0x1dc);
                    do {
                        *puVar7 = *(undefined4*)(local_98[probeIndex] + 0x10);
                        probeIndex = probeIndex + 1;
                        puVar7 = puVar7 + 1;
                    } while (probeIndex < *(uint*)(thisPtr + 0x1d8));
                }
            } else {
                *(undefined4*)(thisPtr + 0x1d8) = 0;
            }
            FUN_0088a7b0();
            probeIndex = 0;
            if (*(int*)(thisPtr + 0x1d8) != 0) {
                uint* pProbeID = (uint*)(thisPtr + 0x1dc);
                do {
                    local_bc = *pProbeID;
                    iVar6 = FUN_00889ee0(&local_bc);
                    if (((iVar6 != 0) && (iVar6 = *(int*)(iVar6 + 0x14), iVar6 != 0)) &&
                        ((byteFlag = *(char*)(iVar6 + 0x50), iVar5 = iVar6, byteFlag == '\x01' ||
                        ((byteFlag == '\x06' || (byteFlag == '\x03')))))) {
                        do {
                            if ((*(byte*)(iVar5 + 0x51) & 8) == 0) {
                                *(byte*)(iVar5 + 0x51) = *(byte*)(iVar5 + 0x51) | 8;
                                if (*(uint*)(thisPtr + 0x1c0) < 0x20) {
                                    *(int*)(thisPtr + 0x140 + *(uint*)(thisPtr + 0x1c0) * 4) = iVar5;
                                    *(int*)(thisPtr + 0x1c0) = *(int*)(thisPtr + 0x1c0) + 1;
                                }
                            }
                            piVar9 = (int*)(iVar5 + 0x70);
                            iVar5 = *piVar9;
                        } while (*piVar9 != iVar6);
                    }
                    pProbeID = pProbeID + 1;
                    probeIndex = probeIndex + 1;
                } while (probeIndex < *(uint*)(thisPtr + 0x1d8));
            }
            floatVal = _DAT_00d5780c;
            local_bc = 0;
            if (*(int*)(thisPtr + 0x90) - *(int*)(thisPtr + 0x8c) >> 2 != 0) {
                do {
                    iVar6 = *(int*)(*(int*)(thisPtr + 0x8c) + local_bc * 4);
                    if ((*(ushort*)(iVar6 + 0x10) & 2) == 0) {
                        if (*(char*)(thisPtr + 0xad) == '\0') {
                            *(undefined4*)(iVar6 + 0xc) = 0;
                        } else {
                            if (*(int*)(iVar6 + 0x18) == 0) {
                                *(undefined4*)(iVar6 + 0xc) = 0;
                            } else if ((*(ushort*)(iVar6 + 0x10) & 8) == 0) {
                                uint* pBestProbe = (uint*)0x0;
                                uint* pCurrentProbe = (uint*)0x0;
                                iVar5 = 3;
                                pfSource = cameraTransform;
                                do {
                                    diffX = *(float*)(iVar6 + 0x20) - *pfSource;
                                    diffY = *(float*)(iVar6 + 0x24) - pfSource[1];
                                    diffZ = *(float*)(iVar6 + 0x28) - pfSource[2];
                                    distanceSq = SQRT(diffZ * diffZ + diffY * diffY + diffX * diffX);
                                    *(float*)(iVar6 + 0x34) = distanceSq;
                                    if ((distanceSq < *(float*)(iVar6 + 0x38)) || (*(float*)(iVar6 + 0x3c) < distanceSq)) {
                                        local_b4[0] = (uint*)0x0;
                                        bVar12 = (float)pBestProbe == 0.0;
                                        bVar11 = 0.0 < (float)pBestProbe;
                                        ppuVar8 = local_b4;
                                    } else {
                                        local_b8 = (uint*)((floatVal - distanceSq / *(float*)(thisPtr + 0x284)) * DAT_00d5e288);
                                        bVar12 = (float)local_b8 == (float)pBestProbe;
                                        bVar11 = (float)local_b8 < (float)pBestProbe;
                                        ppuVar8 = &local_b8;
                                    }
                                    if (bVar11 || bVar12) {
                                        ppuVar8 = &pCurrentProbe;
                                    }
                                    pBestProbe = *ppuVar8;
                                    pfSource = pfSource + 4;
                                    iVar5 = iVar5 + -1;
                                    pCurrentProbe = pBestProbe;
                                } while (iVar5 != 0);
                                *(uint**)(iVar6 + 0xc) = pBestProbe;
                            } else {
                                *(undefined4*)(iVar6 + 0xc) = DAT_00e54288;
                            }
                            probeIndex = *(uint*)(iVar6 + 4);
                            if (probeIndex != 0) {
                                for (puVar8 = *(uint**)(*(int*)(DAT_0122337c + 0x50) +
                                    (probeIndex % *(uint*)(DAT_0122337c + 0x54)) * 4);
                                    puVar8 != (uint*)0x0; puVar8 = (uint*)puVar8[2]) {
                                    if (*puVar8 == probeIndex) {
                                        if ((puVar8 != (uint*)0x0) && (puVar8[1] != 0)) {
                                            iVar5 = *(int*)(puVar8[1] + 0x24);
                                            goto LAB_0088ac20;
                                        }
                                        break;
                                    }
                                }
                                iVar5 = -1;
                                LAB_0088ac20:
                                if ((iVar5 == 1) || (iVar5 == 3)) {
                                    *(float*)(iVar6 + 0xc) = *(float*)(thisPtr + 0x288) + *(float*)(iVar6 + 0xc);
                                }
                            }
                        }
                    }
                    local_bc = local_bc + 1;
                } while (local_bc < (uint)(*(int*)(thisPtr + 0x90) - *(int*)(thisPtr + 0x8c) >> 2));
            }
            probeIndex = 0;
            if (*(int*)(thisPtr + 0x1c0) != 0) {
                piVar9 = (int*)(thisPtr + 0x140);
                do {
                    *(byte*)(*piVar9 + 0x51) = *(byte*)(*piVar9 + 0x51) & 0xf7;
                    probeIndex = probeIndex + 1;
                    piVar9 = piVar9 + 1;
                } while (probeIndex < *(uint*)(thisPtr + 0x1c0));
            }
        }
    }
    return;
}