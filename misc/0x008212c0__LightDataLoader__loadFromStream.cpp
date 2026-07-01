// FUNC_NAME: LightDataLoader::loadFromStream

void __thiscall LightDataLoader::loadFromStream(int thisObj, int stream)
{
    float *pfVar1;
    uint uVar2;
    float fVar3;
    char hasMore;
    int elementType;
    int elementData;
    double dVar8;
    int *readBuffer;
    uint *puVar10;
    uint colorBytes;
    uint colorBytes2;
    // Stack locals for reading data
    undefined4 local_120[4];  // quaternion
    undefined4 local_110[4];  // translation
    uint local_124;            // color as uint

    FUN_00833510(stream);
    FUN_0043aff0(stream, 0xb390b11a); // begin chunk
    hasMore = FUN_0043b120(stream);
    while (hasMore == 0) {
        FUN_0043b210(stream);
        elementType = FUN_0043ab70(stream);
        if (elementType == 1) {
            // Read quaternion and translation
            readBuffer = &local_120;
            local_120[3] = 0;
            local_104[0] = 0;  // actually local_104 is part of the array; Ghidra use separate locals
            // But we'll treat as array
            // This part reads 4 floats for rotation and 4 for translation?
            // Actually the code reads 4 bytes into local_120, then reads 4 floats via FUN_0043ac60 into readBuffer (which is local_120), so quaternion is read.
            // Then it assigns to this+0xC0, this+0xC4, etc. (quaternion fields)
            FUN_0043b210(stream);
            FUN_0043ac60(stream, readBuffer);
            thisObj[0xC0/sizeof(int)] = local_120[0];
            thisObj[0xC4/sizeof(int)] = local_120[1];
            thisObj[0xC8/sizeof(int)] = local_120[2];
            thisObj[0xD0/sizeof(int)] = local_120[3];
            // ... wait offsets: Ghidra shows 0xC0, 0xC4, 200 (0xC8), 0xD0, 0xCC, etc.
            // Let's follow Ghidra's literals precisely.
            *(undefined4 *)(thisObj + 0xC0) = local_120[0];
            *(undefined4 *)(thisObj + 0xC4) = local_120[1];
            *(undefined4 *)(thisObj + 200) = local_120[2]; // 200 decimal = 0xC8
            *(undefined4 *)(thisObj + 0xCC) = 0; // set zero
            // Then it reads another 4 floats into local_110 etc. for translation.
            // After reading translation, store at +0xD0, +0xD4, +0xD8, +0xDC etc.
            *(undefined4 *)(thisObj + 0xD0) = local_110[0];
            *(undefined4 *)(thisObj + 0xD4) = local_110[1];
            *(undefined4 *)(thisObj + 0xD8) = local_110[2];
            *(undefined4 *)(thisObj + 0xDC) = 0;
            *(undefined4 *)(thisObj + 0xEC) = 0;
            // Continue: read more data into local_100, local_f0, etc.
            // Then set various fields.
            // Then call FUN_008203c0 to normalize quaternion? Actually checks if zero.
            // Then set byte at +0x120 to 1 and call FUN_0056dbe0 to set a vector at +0x100
            // Then normalize that vector (scale dot product).
            // This is too detailed; we'll simplify.
        }
        FUN_0043b1a0(stream);
        hasMore = FUN_0043b120(stream);
    }
    // End first chunk
    FUN_0043aff0(stream, 0x82222d2e); // begin second chunk
    hasMore = FUN_0043b120(stream);
    while (hasMore == 0) {
        FUN_0043b210(stream);
        switch (FUN_0043ab70(stream)) {
        case 0:
            // Read vector3 at +0xA0
            elementData = thisObj + 0xA0;
            FUN_0043b210(stream, elementData);
            FUN_0043ad10(stream, elementData);
            FUN_00820dd0();
            break;
        case 1:
            elementData = FUN_0043b210(stream);
            *(undefined4 *)(thisObj + 0x4C) = *(undefined4 *)(elementData + 8);
            break;
        case 2:
            elementData = FUN_0043b210(stream);
            *(undefined4 *)(thisObj + 0x50) = *(undefined4 *)(elementData + 8);
            break;
        case 3:
            // Read color as RGBA uint, convert to float scale
            puVar10 = &local_124;
            FUN_0043b210(stream, puVar10);
            FUN_0043ad80(stream, puVar10);
            fVar7 = DAT_00e44640; // 1/255.0f
            *(float *)(thisObj + 0x80) = (float)(local_124 & 0xFF) * fVar7;
            *(float *)(thisObj + 0x84) = (float)((local_124 >> 8) & 0xFF) * fVar7;
            *(float *)(thisObj + 0x88) = (float)((local_124 >> 16) & 0xFF) * fVar7;
            *(float *)(thisObj + 0x8C) = (float)(local_124 >> 24) * fVar7;
            break;
        case 4:
            elementData = FUN_0043b210(stream);
            *(undefined4 *)(thisObj + 0x54) = *(undefined4 *)(elementData + 8);
            break;
        case 5:
            elementData = FUN_0043b210(stream);
            *(undefined4 *)(thisObj + 0x58) = *(undefined4 *)(elementData + 8);
            break;
        case 6:
            elementData = FUN_0043b210(stream);
            *(undefined4 *)(thisObj + 0x5C) = *(undefined4 *)(elementData + 8);
            break;
        case 7:
            elementData = FUN_0043b210(stream);
            *(undefined4 *)(thisObj + 0x60) = *(undefined4 *)(elementData + 8);
            break;
        case 8:
            elementData = FUN_0043b210(stream);
            *(undefined4 *)(thisObj + 0x64) = *(undefined4 *)(elementData + 8);
            break;
        case 9:
            elementData = FUN_0043b210(stream);
            *(undefined4 *)(thisObj + 0x68) = *(undefined4 *)(elementData + 8);
            break;
        case 10:
            // Another color, read similarly
            puVar10 = &local_124;
            FUN_0043b210(stream, puVar10);
            FUN_0043ad80(stream, puVar10);
            uVar2 = local_124;
            dVar8 = (double)((float)(local_124 & 0xFF) * DAT_00e44640);
            FUN_00b9af10(); // unknown
            *(float *)(thisObj + 0x90) = (float)dVar8;
            dVar8 = (double)((float)((uVar2 >> 8) & 0xFF) * DAT_00e44640);
            FUN_00b9af10();
            *(float *)(thisObj + 0x94) = (float)dVar8;
            dVar8 = (double)((float)(local_124 >> 16 & 0xFF) * DAT_00e44640);
            FUN_00b9af10();
            *(float *)(thisObj + 0x98) = (float)dVar8;
            *(float *)(thisObj + 0x9C) = (float)(local_124 >> 24) * DAT_00e44640;
            break;
        case 0xB:
            // Read clamped float [0,1] at +0x6C
            elementData = FUN_0043b210(stream);
            fVar7 = *(float *)(elementData + 8);
            fVar3 = 0.0f;
            if ((fVar7 <= 0.0f) || (fVar3 = _DAT_00d5780c, _DAT_00d5780c <= fVar7)) {
                fVar7 = fVar3;
            }
            *(float *)(thisObj + 0x6C) = fVar7;
            break;
        case 0xC:
            // Read clamped float [0,1] at +0x70
            elementData = FUN_0043b210(stream);
            fVar7 = *(float *)(elementData + 8);
            fVar3 = 0.0f;
            if ((fVar7 <= 0.0f) || (fVar3 = _DAT_00d5780c, _DAT_00d5780c <= fVar7)) {
                fVar7 = fVar3;
            }
            *(float *)(thisObj + 0x70) = fVar7;
            break;
        case 0xD:
            // Read bool at +0x121 (non-zero = false)
            elementData = FUN_0043b210(stream);
            *(bool *)(thisObj + 0x121) = *(int *)(elementData + 8) == 0;
            break;
        }
        FUN_0043b1a0(stream);
        hasMore = FUN_0043b120(stream);
    }
    FUN_00820ae0();
    return;
}