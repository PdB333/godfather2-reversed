// FUNC_NAME: GameObject::readPropertiesFromStream
void __thiscall GameObject::readPropertiesFromStream(int thisObj, int stream)
{
    char hasMoreData;
    int *pItemData;
    int readValue;
    int itemType;
    char localArray[12]; // 12-byte buffer
    int localInts[4]; // but only local_f4, e4, d4, c4 used? Actually c4 set from global
    int local_50[19]; // 76 bytes, probably buffer for conversion
    int local_170; // temporary for rounding

    // Initialize stream reading?
    FUN_0046c710(stream);

    // Read 4 ints at +0x11c (probably rotation quaternion)
    int *quatSrc = (int *)FUN_0043ab10(); // returns pointer to 4 ints (e.g., quaternion)
    *(int *)(thisObj + 0x11c) = *quatSrc;
    *(int *)(thisObj + 0x120) = quatSrc[1];
    *(int *)(thisObj + 0x124) = quatSrc[2];
    *(int *)(thisObj + 0x128) = quatSrc[3];

    // Begin reading a chunk with hash 0xb390b11a (e.g., "Transform" chunk)
    FUN_0043aff0(stream, 0xb390b11a);
    FUN_0043af00(1); // set mode?
    hasMoreData = FUN_0043b120(); // check if chunk has data

    if (hasMoreData == '\0') {
        // Read and convert another 12-byte structure (maybe position)
        int *pArray = localArray;
        localInts[0] = 0;
        localInts[1] = 0;
        localInts[2] = 0;
        localInts[3] = _DAT_00d5780c; // some global constant (maybe scale or axis)
        FUN_0043b210(pArray); // read 12 bytes into localArray
        FUN_0043ad90(pArray); // parse to something? (quaternion conversion?)
        FUN_0044b4e0(local_50, localArray); // convert to 76-byte representation
        FUN_0056d530(local_50, thisObj + 0x100); // store part at +0x100 (8 bytes? 12?)
        // Overwrite upper part of that area
        *(undefined8 *)(thisObj + 0x110) = *(undefined8 *)(&local_50[0]); // depends on layout; actually from local_d0 and local_c8 in decompiler
        *(int *)(thisObj + 0x118) = *(int *)((int)&localArray + 20); // simplified; original uses local_d0 and local_c8
        // Note: original used local_d0 (undefined8) and local_c8 (undefined4) which came from local_50 conversion?
    }

    // Now read a second chunk with hash 0x26805035 (e.g., "Properties" chunk)
    FUN_0043aff0(stream, 0x26805035);
    hasMoreData = FUN_0043b120(); // check again

    do {
        if (hasMoreData != '\0') {
            // Unknown: maybe finish reading?
            FUN_0083a140(thisObj);
            return;
        }

        // Get next item
        FUN_0043b210(); // advance stream?
        itemType = FUN_0043ab70(); // get item type ID

        switch (itemType) {
        case 4: // read something and call delegate
            FUN_0043b210();
            readValue = FUN_0043ab90(); // read an int or float
            FUN_004d3d90(readValue); // apply to something (maybe audio or animation)
            break;
        case 5: // set flag bit 3 (0x8) at +0xe8
            pItemData = (int *)FUN_0043b210();
            if (*(int *)(pItemData + 2) == 0) { // pItemData+8 is third element? Actually pItemData+0x8?
                *(unsigned int *)(thisObj + 0xe8) &= 0xfffffff7; // clear bit 3
            } else {
                *(unsigned int *)(thisObj + 0xe8) |= 8; // set bit 3
            }
            break;
        case 6: // similar to case 4
            FUN_0043b210();
            readValue = FUN_0043ab90();
            FUN_004d3d90(readValue);
            break;
        case 7: // store int at +0x70 (offset 0x70)
            pItemData = (int *)FUN_0043b210();
            *(int *)(thisObj + 0x70) = *(int *)((int)pItemData + 8);
            break;
        case 8: // store int at +0x74
            pItemData = (int *)FUN_0043b210();
            *(int *)(thisObj + 0x74) = *(int *)((int)pItemData + 8);
            break;
        case 9: // +0x78
            pItemData = (int *)FUN_0043b210();
            *(int *)(thisObj + 0x78) = *(int *)((int)pItemData + 8);
            break;
        case 10: // +0x7c
            pItemData = (int *)FUN_0043b210();
            *(int *)(thisObj + 0x7c) = *(int *)((int)pItemData + 8);
            break;
        case 0xb: // +0x80
            pItemData = (int *)FUN_0043b210();
            *(int *)(thisObj + 0x80) = *(int *)((int)pItemData + 8);
            break;
        case 0xc: // +0x84
            pItemData = (int *)FUN_0043b210();
            *(int *)(thisObj + 0x84) = *(int *)((int)pItemData + 8);
            break;
        case 0xd: // +0x88
            pItemData = (int *)FUN_0043b210();
            *(int *)(thisObj + 0x88) = *(int *)((int)pItemData + 8);
            break;
        case 0xe: // float multiplied by global constant and stored at +0x8c (rounded)
            pItemData = (int *)FUN_0043b210();
            // Read float from pItemData+8, multiply by _DAT_00d73d00, round to int
            local_170 = (int)(long long)(*(float *)((int)pItemData + 8) * _DAT_00d73d00);
            *(int *)(thisObj + 0x8c) = local_170;
            break;
        case 0xf: // store int at +0x90
            pItemData = (int *)FUN_0043b210();
            *(int *)(thisObj + 0x90) = *(int *)((int)pItemData + 8);
            break;
        case 0x10: // flag bit 0
            pItemData = (int *)FUN_0043b210();
            if (*(int *)((int)pItemData + 8) == 0) {
                *(unsigned int *)(thisObj + 0xe8) &= 0xfffffffe; // clear bit 0
            } else {
                *(unsigned int *)(thisObj + 0xe8) |= 1; // set bit 0
            }
            break;
        case 0x11: // flag bit 1
            pItemData = (int *)FUN_0043b210();
            if (*(int *)((int)pItemData + 8) == 0) {
                *(unsigned int *)(thisObj + 0xe8) &= 0xfffffffd; // clear bit 1
            } else {
                *(unsigned int *)(thisObj + 0xe8) |= 2; // set bit 1
            }
            break;
        // Cases 0x12-0x1b: each reads a value and stores via helper at offsets 0x94,0x9c,...0xdc (spaced by 8)
        case 0x12:
            FUN_0043b210();
            readValue = FUN_0043ab90(); // read a 4-byte value
            FUN_00408980(thisObj + 0x94, readValue); // store as 8-byte structure? (function takes dest and value)
            break;
        case 0x13:
            FUN_0043b210();
            readValue = FUN_0043ab90();
            FUN_00408980(thisObj + 0x9c, readValue);
            break;
        case 0x14:
            FUN_0043b210();
            readValue = FUN_0043ab90();
            FUN_00408980(thisObj + 0xa4, readValue);
            break;
        case 0x15:
            FUN_0043b210();
            readValue = FUN_0043ab90();
            FUN_00408980(thisObj + 0xac, readValue);
            break;
        case 0x16:
            FUN_0043b210();
            readValue = FUN_0043ab90();
            FUN_00408980(thisObj + 0xb4, readValue);
            break;
        case 0x17:
            FUN_0043b210();
            readValue = FUN_0043ab90();
            FUN_00408980(thisObj + 0xbc, readValue);
            break;
        case 0x18:
            FUN_0043b210();
            readValue = FUN_0043ab90();
            FUN_00408980(thisObj + 0xc4, readValue);
            break;
        case 0x19:
            FUN_0043b210();
            readValue = FUN_0043ab90();
            FUN_00408980(thisObj + 0xcc, readValue);
            break;
        case 0x1a:
            FUN_0043b210();
            readValue = FUN_0043ab90();
            FUN_00408980(thisObj + 0xd4, readValue);
            break;
        case 0x1b:
            FUN_0043b210();
            readValue = FUN_0043ab90();
            FUN_00408980(thisObj + 0xdc, readValue);
            break;
        }

        // Advance to next item
        FUN_0043b1a0();
        hasMoreData = FUN_0043b120(); // check if more items in chunk
    } while (true);
}