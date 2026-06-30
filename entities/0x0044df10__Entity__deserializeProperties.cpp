// FUNC_NAME: Entity::deserializeProperties
void Entity::deserializeProperties(int thisObj, void* stream)  // thisObj at ecx, stream as parameter
{
    char cVar1;
    undefined4 uVar2;
    ushort uVar3;
    undefined4* puVar4;
    undefined4** ppuVar5;
    undefined4** extraout_EDX;
    undefined4** ppuVar6;
    uint uVar7;
    bool bVar8;
    float fVar9;
    float fVar10;
    char iteratorState[4];
    int bitmapBase;
    undefined4* currentPtr;
    uint currentIndex;
    uint totalCount;
    undefined4* currentProperty;
    undefined2 currentIndexShort;
    undefined4 propertyType;
    undefined4 propertyValue;
    undefined4** nextPtrList;
    ushort lookupBuffer[16];
    char modeFlag; // local_78
    int someCount; // local_6c
    int someBase; // local_68
    int* somePtr; // local_1c

    // Validate stream with magic number
    checkStreamMagic(stream, 0xb390b11a);
    setStreamMode(1);

    // Determine iteration mode: pointer list or bitmap
    if (modeFlag == 0) {
        bVar8 = *somePtr == 0;  // pointer list termination
    } else {
        bVar8 = someCount == someBase;  // bitmap count
    }
    if (!bVar8) {
        currentIndex = 0;
        propertyType = 0;
        propertyValue = 0;
        // Some constant
        // DAT_00e2b1a4
        initPropertyIterator(iteratorState);
        readPropertiesToBuffer(thisObj + 0x10, iteratorState);  // copy buffer to offset 0x10
    }

    uVar2 = DAT_0110ac04; // global default value
    *(undefined2*)(thisObj + 0x56) = 0xc007;  // flags
    *(undefined4*)(thisObj + 0x58) = uVar2;    // field at 0x58

    checkStreamMagic(stream, 0x580e3e39);
    ppuVar6 = nextPtrList;
    uVar7 = currentIndex;
    fVar9 = DAT_00e445c8;  // scaling factor?
    fVar10 = DAT_00e44584; // another factor?
    cVar1 = iteratorState[0];  // iteration mode flag (0 = pointer, non-zero = bitmap)

    while (true) {
        if (cVar1 == 0) {
            bVar8 = *ppuVar6 == (undefined4*)0x0;  // null pointer terminates list
        } else {
            bVar8 = uVar7 == totalCount;  // bitmap mode: index == total count
        }
        if (bVar8) break;

        ppuVar5 = &currentProperty; // default to currentProperty if bitmap mode
        if (cVar1 == 0) {
            ppuVar5 = ppuVar6; // pointer mode: use the pointer from list
        }

        // Get property ID: either from offset 6 of the item (if type 0x25e3) or from second word
        if (*(short*)((int)ppuVar5 + 6) == 0x25e3) {
            puVar4 = (undefined4*)(uint)*(ushort*)(ppuVar5 + 1);
        } else {
            puVar4 = ppuVar5[1];
        }

        switch (puVar4) {
        case 0x0:  // type 0: property value (byte?)
            ppuVar5 = &currentProperty;
            if (cVar1 == 0) ppuVar5 = ppuVar6;
            *(undefined1*)(thisObj + 0x54) = *(undefined1*)(ppuVar5 + 2);
            break;
        case 0x1:  // type 1: value for field at 0x70, possibly scaled
            ppuVar5 = &currentProperty;
            if (cVar1 == 0) ppuVar5 = ppuVar6;
            puVar4 = ppuVar5[2];  // third element of property item
            *(undefined4**)(thisObj + 0x70) = puVar4;
            // Check global byte array at offset based on field at 0x54
            if (*(char*)((int)&PTR_DAT_00e35658 + (uint)*(byte*)(thisObj + 0x54)) != 0) {
                *(float*)(thisObj + 0x70) = (float)puVar4 * fVar9;
            }
            break;
        case 0x2:  // type 2: value at 0x6c
            ppuVar5 = &currentProperty;
            if (cVar1 == 0) ppuVar5 = ppuVar6;
            *(undefined4**)(thisObj + 0x6c) = ppuVar5[2];
            break;
        case 0x3:  // type 3: flag bit manipulation based on value
            ppuVar5 = &currentProperty;
            if (cVar1 == 0) ppuVar5 = ppuVar6;
            if (ppuVar5[2] == (undefined4*)0x7fffffff) {
                uVar3 = 0xc003;
            } else {
                uVar3 = getRandomValue();  // FUN_004ab0a0
                ppuVar6 = extraout_EDX;
            }
            *(ushort*)(thisObj + 0x56) = *(ushort*)(thisObj + 0x56) & 0x3ffc | uVar3;
            break;
        case 0x4:  // type 4: value at 0x58 with default fallback
            ppuVar5 = &currentProperty;
            if (cVar1 == 0) ppuVar5 = ppuVar6;
            puVar4 = ppuVar5[2];
            *(undefined4**)(thisObj + 0x58) = puVar4;
            if (puVar4 == (undefined4*)0x0) {
                *(undefined4*)(thisObj + 0x58) = DAT_0110ac04;  // global default
            }
            break;
        case 0x5:  // type 5: value at 0x5c
            ppuVar5 = &currentProperty;
            if (cVar1 == 0) ppuVar5 = ppuVar6;
            *(undefined4**)(thisObj + 0x5c) = ppuVar5[2];
            break;
        case 0x6:  // type 6: value at 0x64 (100 decimal)
            ppuVar5 = &currentProperty;
            if (cVar1 == 0) ppuVar5 = ppuVar6;
            *(undefined4**)(thisObj + 100) = ppuVar5[2];
            break;
        case 0x7:  // type 7: value at 0x78, possibly scaled
            ppuVar5 = &currentProperty;
            if (cVar1 == 0) ppuVar5 = ppuVar6;
            puVar4 = ppuVar5[2];
            *(undefined4**)(thisObj + 0x78) = puVar4;
            if (*(char*)((int)&PTR_DAT_00e35658 + (uint)*(byte*)(thisObj + 0x54)) != 0) {
                *(float*)(thisObj + 0x78) = (float)puVar4 * fVar9;
            }
            break;
        case 0x8:  // type 8: value at 0x74
            ppuVar5 = &currentProperty;
            if (cVar1 == 0) ppuVar5 = ppuVar6;
            *(undefined4**)(thisObj + 0x74) = ppuVar5[2];
            break;
        case 0x9:  // type 9: value at 0x60
            ppuVar5 = &currentProperty;
            if (cVar1 == 0) ppuVar5 = ppuVar6;
            *(undefined4**)(thisObj + 0x60) = ppuVar5[2];
            break;
        case 0xa:  // type 10: set 2 bits in flags using lookup table
            lookupBuffer[0xc] = 8;
            lookupBuffer[0xd] = 0;
            lookupBuffer[0xe] = 8;
            lookupBuffer[0xf] = 0;
            lookupBuffer[8] = 0;
            lookupBuffer[9] = 0;
            lookupBuffer[10] = 4;
            lookupBuffer[0xb] = 0;
            ppuVar5 = &currentProperty;
            if (cVar1 == 0) ppuVar5 = ppuVar6;
            *(ushort*)(thisObj + 0x56) = 
                *(ushort*)(thisObj + 0x56) & 0xfff3 | 
                lookupBuffer[(int)ppuVar5[2] * 2 + 8];
            break;
        case 0xb:  // type 11: set 3 bits in flags using lookup table
            lookupBuffer[0] = 0;
            lookupBuffer[1] = 0;
            lookupBuffer[2] = 0x20;
            lookupBuffer[3] = 0;
            lookupBuffer[4] = 0x40;
            lookupBuffer[5] = 0;
            lookupBuffer[6] = 0x60;
            lookupBuffer[7] = 0;
            ppuVar5 = &currentProperty;
            if (cVar1 == 0) ppuVar5 = ppuVar6;
            *(ushort*)(thisObj + 0x56) = 
                *(ushort*)(thisObj + 0x56) & 0xff9f | 
                lookupBuffer[(int)ppuVar5[2] * 2];
            break;
        case 0xc:  // type 12: value at 0x68
            ppuVar5 = &currentProperty;
            if (cVar1 == 0) ppuVar5 = ppuVar6;
            *(undefined4**)(thisObj + 0x68) = ppuVar5[2];
            break;
        case 0xd:  // type 13: value at 0x7c
            ppuVar5 = &currentProperty;
            if (cVar1 == 0) ppuVar5 = ppuVar6;
            *(undefined4**)(thisObj + 0x7c) = ppuVar5[2];
            break;
        case 0xe:  // type 14: set/clear bit 4 in flags
            ppuVar5 = &currentProperty;
            if (cVar1 == 0) ppuVar5 = ppuVar6;
            if (ppuVar5[2] == (undefined4*)0x0) {
                *(ushort*)(thisObj + 0x56) = *(ushort*)(thisObj + 0x56) & 0xffef;  // clear bit 4
            } else {
                *(ushort*)(thisObj + 0x56) = *(ushort*)(thisObj + 0x56) | 0x10;   // set bit 4
            }
            break;
        case 0xf:  // type 15: set 3 bytes at 0x80-0x82
            ppuVar5 = &currentProperty;
            if (cVar1 == 0) ppuVar5 = ppuVar6;
            puVar4 = ppuVar5[2];
            *(char*)(thisObj + 0x80) = (char)puVar4;
            *(char*)(thisObj + 0x81) = (char)((uint)puVar4 >> 8);
            *(char*)(thisObj + 0x82) = (char)((uint)puVar4 >> 0x10);
            break;
        case 0x10: // type 16: scaled byte at 0x83
            ppuVar5 = &currentProperty;
            if (cVar1 == 0) ppuVar5 = ppuVar6;
            *(char*)(thisObj + 0x83) = (char)(int)((float)ppuVar5[2] * fVar10);
            break;
        case 0x11: // type 17: set/clear bit 7 in flags
            ppuVar5 = &currentProperty;
            if (cVar1 == 0) ppuVar5 = ppuVar6;
            if (ppuVar5[2] == (undefined4*)0x0) {
                *(ushort*)(thisObj + 0x56) = *(ushort*)(thisObj + 0x56) & 0xff7f;  // clear bit 7
            } else {
                *(ushort*)(thisObj + 0x56) = *(ushort*)(thisObj + 0x56) | 0x80;   // set bit 7
            }
            break;
        case 0x12: // type 18: value at 0x50
            ppuVar5 = &currentProperty;
            if (cVar1 == 0) ppuVar5 = ppuVar6;
            *(undefined4**)(thisObj + 0x50) = ppuVar5[2];
            break;
        }

        // Advance to next property
        if (cVar1 == 0) {
            // Pointer mode: advance through linked list
            if ((int)uVar7 < 0) {
                nextPtrList = (undefined4**)((int)ppuVar6 + (int)*ppuVar6);
                advancePointerIterator();  // FUN_0043b140
                ppuVar6 = nextPtrList;
                uVar7 = currentIndex;
                cVar1 = iteratorState[0];
            } else if ((int)uVar7 < (int)(totalCount - 1)) {
                currentIndex = uVar7 + 1;
                nextPtrList = (undefined4**)((int)ppuVar6 + (int)*ppuVar6);
                ppuVar6 = (undefined4**)((int)ppuVar6 + (int)*ppuVar6);
                uVar7 = currentIndex;
            } else {
                nextPtrList = (undefined4**)0x01163cf8;  // sentinel address
                ppuVar6 = (undefined4**)0x01163cf8;
            }
        } else {
            // Bitmap mode: advance using bitmask
            currentIndex = uVar7 + 1;
            uVar7 = currentIndex;
            if (currentIndex != totalCount) {
                currentIndexShort = (short)currentIndex;
                if ((*(byte*)((currentIndex >> 3) + bitmapBase) & (byte)(1 << ((byte)currentIndex & 7))) == 0) {
                    currentProperty = currentPtr;
                    propertyType = *currentPtr;
                    currentPtr = currentPtr + 1;
                } else {
                    currentProperty = (undefined4*)0x0;
                    propertyType = 0;
                }
            }
        }
    }
    return;
}