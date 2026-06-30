// FUNC_NAME: EntityDataManager::readQuantizedDeltaValues
void EntityDataManager::readQuantizedDeltaValues(void* this_, unsigned char** dataPtr, int* outValues, int* runningDelta)
{
    byte bVar1;
    byte bVar2;
    bool secondSymbolDone;
    ushort uVar4;
    short sVar5;
    short sVar6;
    uint controlByte;
    unsigned char* pbVar8;
    unsigned char* pbVar9;
    int iVar10;

    pbVar9 = *dataPtr;
    sVar5 = 0;
    sVar6 = 0;
    
    if (*(char*)(this_ + 8) == '\0') {
        // Original encoding mode
        bVar1 = *pbVar9;
        pbVar8 = pbVar9 + 1;
        if ((bVar1 & 0x10) == 0) {
            sVar5 = 0x1000; // Default large value (after shift: 0x10000)
        } else {
            bVar2 = *pbVar8;
            pbVar8 = pbVar9 + 3;
            sVar5 = (ushort)bVar2 * 0x100 + (ushort)pbVar9[2];
        }
        if ((bVar1 & 0x20) == 0) {
            sVar6 = 0x1000;
        } else {
            bVar2 = *pbVar8;
            pbVar9 = pbVar8 + 1;
            pbVar8 = pbVar8 + 2;
            sVar6 = (ushort)bVar2 * 0x100 + (ushort)*pbVar9;
        }
        outValues[2] = (int)sVar6 << 4; // +0x??, shift by 4
        outValues[0] = (int)sVar5 << 4;
        outValues[1] = 0;
        outValues[3] = 0;
        
        if ((bVar1 & 0x40) == 0) {
            uVar4 = (ushort)*pbVar8;
            pbVar9 = pbVar8 + 1;
        } else {
            pbVar9 = pbVar8 + 2;
            uVar4 = CONCAT11(*pbVar8, pbVar8[1]); // little-endian 16-bit read
        }
        *(ushort*)(outValues + 5) = uVar4;
        
        if (-1 < (char)bVar1) { // bit 0x80 clear
            outValues[4] = (uint)(ushort)((ushort)*pbVar9 * 0x100 + (ushort)pbVar9[1]);
            *dataPtr = pbVar9 + 2;
            return;
        }
        outValues[4] = (uint)CONCAT21(CONCAT11(*pbVar9, pbVar9[1]), pbVar9[2]); // 24-bit read
        *dataPtr = pbVar9 + 3;
        return;
    }
    
    // Compressed encoding mode (base-6)
    pbVar8 = pbVar9 + 1;
    secondSymbolDone = false;
    controlByte = (uint)*pbVar9;
    do {
        switch (controlByte % 6) {
        case 0:
            sVar5 = 0x1000;
            goto LAB_00678b41;
        case 1:
            sVar6 = (short)(char)*pbVar8;
            sVar5 = 0x1000;
            pbVar8 = pbVar8 + 1;
            break;
        case 2:
            bVar1 = *pbVar8;
            pbVar9 = pbVar8 + 1;
            pbVar8 = pbVar8 + 2;
            sVar6 = (ushort)bVar1 * 0x100 + (ushort)*pbVar9;
            sVar5 = 0x1000;
            break;
        case 3:
            if (*(char*)(this_ + 0x35) == '\0') {
                sVar5 = (ushort)*pbVar8 * 0x100 + (ushort)pbVar8[1];
                sVar6 = (short)(char)pbVar8[2];
                pbVar8 = pbVar8 + 3;
            } else {
                sVar5 = (*pbVar8 + 1) * 0x20;
                sVar6 = (short)(char)pbVar8[1];
                pbVar8 = pbVar8 + 2;
            }
            break;
        case 4:
            if (*(char*)(this_ + 0x35) == '\0') {
                pbVar9 = pbVar8 + 2;
                sVar5 = (ushort)*pbVar8 * 0x100 + (ushort)pbVar8[1];
            } else {
                sVar5 = (*pbVar8 + 1) * 0x20;
                pbVar9 = pbVar8 + 1;
            }
            pbVar8 = pbVar9 + 2;
            sVar6 = (ushort)*pbVar9 * 0x100 + (ushort)pbVar9[1];
            break;
        case 5:
            sVar5 = 0;
LAB_00678b41:
            sVar6 = 0;
            break;
        }
        
        if (secondSymbolDone) {
            outValues[2] = (int)sVar5 << 4;
            outValues[3] = (int)sVar6 << 0x10;
            switch (controlByte / 6) {
            case 0:
                bVar1 = *pbVar8;
                iVar10 = *runningDelta - (uint)bVar1;
                outValues[4] = iVar10;
                *runningDelta = iVar10;
                *(ushort*)(outValues + 5) = (ushort)bVar1;
                *dataPtr = pbVar8 + 1;
                return;
            case 1:
                bVar1 = *pbVar8;
                iVar10 = *runningDelta - (uint)(ushort)(bVar1 + 0x100);
                outValues[4] = iVar10;
                *runningDelta = iVar10;
                *(ushort*)(outValues + 5) = bVar1 + 0x100;
                *dataPtr = pbVar8 + 1;
                return;
            case 2:
                uVar4 = (ushort)*pbVar8 * 0x100 + (ushort)pbVar8[1];
                iVar10 = *runningDelta - (uint)uVar4;
                outValues[4] = iVar10;
                *runningDelta = iVar10;
                *(ushort*)(outValues + 5) = uVar4;
                *dataPtr = pbVar8 + 2;
                return;
            case 3:
                bVar1 = *pbVar8;
                bVar2 = pbVar8[1];
                outValues[4] = *runningDelta - (CONCAT21(CONCAT11(bVar1, bVar2), pbVar8[2]) & 0x7fff);
                *(ushort*)(outValues + 5) = CONCAT11(bVar1, bVar2) >> 7;
                *dataPtr = pbVar8 + 3;
                return;
            case 4:
                bVar1 = *pbVar8;
                bVar2 = pbVar8[1];
                outValues[4] = CONCAT21(CONCAT11(bVar1, bVar2), pbVar8[2]) & 0x7fff;
                *(ushort*)(outValues + 5) = CONCAT11(bVar1, bVar2) >> 7;
                *dataPtr = pbVar8 + 3;
                return;
            case 5:
                bVar1 = *pbVar8;
                bVar2 = pbVar8[1];
                outValues[4] = CONCAT31(CONCAT21(CONCAT11(bVar1, bVar2), pbVar8[2]), pbVar8[3]) & 0x7fffff;
                *(ushort*)(outValues + 5) = CONCAT11(bVar1, bVar2) >> 7;
                *dataPtr = pbVar8 + 4;
                return;
            case 6:
                bVar1 = *pbVar8;
                bVar2 = pbVar8[1];
                outValues[4] = (uint)CONCAT21(CONCAT11(pbVar8[2], pbVar8[3]), pbVar8[4]);
                *(ushort*)(outValues + 5) = (ushort)bVar1 * 0x100 + (ushort)bVar2;
                *dataPtr = pbVar8 + 5;
                return;
            default:
                outValues[4] = 0;
                *(ushort*)(outValues + 5) = 0;
                *dataPtr = pbVar8;
                return;
            }
        }
        
        outValues[0] = (int)sVar5 << 4; // First symbol applied
        secondSymbolDone = true;
        outValues[1] = (int)sVar6 << 0x10;
        controlByte = controlByte / 6;
    } while (true);
}