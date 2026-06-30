// FUNC_NAME: NetGhost::unpackUpdate
void __thiscall NetGhost::unpackUpdate(void* thisGhost, NetGhost* destGhost) {
    int classId;
    uint localVar1;
    uint localVar2;
    undefined8* tempPtr;
    bool isExiting;
    undefined8* srcPtr;
    char stringResult;
    int state;
    undefined4 temp1;
    undefined4 temp2;
    undefined4 temp3;
    uint localVar3;
    int* intPtr;
    undefined4 stackVar1;
    undefined8 stackVar2;
    undefined4 stackVar3;
    int stackArray[3];

    srcPtr = destGhost;  // Keep original destGhost pointer
    classId = destGhost->vtable->getTypeId();  // Call first vtable function on destGhost
    if (classId == 0x10ce9029) {  // Type A (e.g., SentryGhost)
        temp1 = (thisGhost->dataInterface + 0x10c)->getData(*(uint*)(thisGhost + 0x14c));  // Read data from buffer
        temp2 = (thisGhost->dataInterface + 0x10c)->getData(*(int*)(thisGhost + 0x14c) + 1);
        temp3 = FUN_00757900(*(uint*)(thisGhost + 0x14c));  // Probably getChunkSize or similar
        FUN_00752b60(temp3, temp1, temp2);
        localVar1 = *(int*)(thisGhost + 0x14c) + 2;
        localVar2 = (thisGhost->dataInterface + 0x10c)->getSize();
        if (localVar1 < localVar2) {
            intPtr = (int*)((thisGhost->dataInterface + 0x10c)->getData(localVar1));
            if (*intPtr != 0) {
                tempPtr = (undefined8*)intPtr[2];
                // Copy transform/position data to dest ghost
                *(undefined8*)((int)srcPtr + 0xbc) = *tempPtr;
                *(undefined4*)((int)srcPtr + 0xc4) = *(undefined4*)(tempPtr + 1);
            }
        }
        state = FUN_00757900(*(int*)(thisGhost + 0x14c) + 1);
        if (state != 3) {
            (thisGhost->dataInterface + 0x10c)->getData(*(int*)(thisGhost + 0x14c) + 1);
            (thisGhost->dataInterface + 0x10c)->getData(*(int*)(thisGhost + 0x14c) + 2);
        }
        // Check if ghost should be marked as "exiting" (bit 0 in flags at +0xa8)
        if (((*(byte*)(thisGhost + 0xa8) & 1) == 0) ||
            (((*(int*)(thisGhost + 0xc0) == 0 || (*(int*)(thisGhost + 0xc0) == 0x48)) &&
             ((*(byte*)(thisGhost + 0xd4) & 1) == 0)))) {
            isExiting = false;
        } else {
            isExiting = true;
        }
        if (isExiting) {
            *(uint*)((int)srcPtr + 0xcc) |= 8;  // Set bit 3 (exiting flag)
        } else {
            *(uint*)((int)srcPtr + 0xcc) &= 0xfffffff7;  // Clear bit 3
        }
        // Copy transform (translation, rotation, scale) from source to dest
        srcPtr[0x1a] = *(undefined8*)(thisGhost + 0x78);
        srcPtr[0x1b] = *(undefined8*)(thisGhost + 0x80);
        srcPtr[0x1c] = *(undefined8*)(thisGhost + 0x88);
        srcPtr[0x1d] = *(undefined8*)(thisGhost + 0x90);
        srcPtr[0x1e] = *(undefined8*)(thisGhost + 0x98);
        srcPtr[0x1f] = *(undefined8*)(thisGhost + 0xa0);
        *(undefined4*)((int)srcPtr + 0x94) = *(undefined4*)(thisGhost + 0xbc);  // Some 4-byte field
    }
    else if (classId == 0x17a70916) {  // Type B (e.g., PlayerGhost)
        state = *(int*)(thisGhost + 0xc);  // AnimState or substate?
        if (state == 2) {
            temp1 = (thisGhost->dataInterface + 0x10c)->getData(*(uint*)(thisGhost + 0x14c));
            FUN_005f6600(temp1);  // Some string operation
            stackVar1 = 0;
            srcPtr = (undefined8*)0x0;  // Shadowing original destGhost pointer (local reuse)
            stringResult = FUN_005f5cb0(&stackVar1, &srcPtr);  // Read string
            if (stringResult != '\0') {
                stackVar2 = *srcPtr;
                stackVar3 = *(undefined4*)(srcPtr + 1);  // Copy string data
            }
            if (stackArray[0] != 0) {
                FUN_004daf90(stackArray);  // Free allocated memory
            }
        }
        else if (state == 7) {
            (thisGhost->dataInterface + 0x10c)->getData(*(uint*)(thisGhost + 0x14c));
            stackVar1 = 0;
            srcPtr = (undefined8*)0x0;
            stringResult = FUN_005f5cb0(&stackVar1, &srcPtr);
            if (stringResult != '\0') {
                stackVar2 = *srcPtr;
                stackVar3 = *(undefined4*)(srcPtr + 1);
            }
        }
        else if (state == 0xb) {
            // Copy attached entity/actor data
            stackVar3 = *(undefined4*)(thisGhost + 0x68);
            stackVar2 = *(undefined8*)(thisGhost + 0x60);
            if ((*(uint*)(thisGhost + 0xa8) >> 9 & 1) != 0) {
                *(uint*)(srcPtr + 0x15) |= 0x200;  // Set "mounted" flag
            }
            FUN_0075cd70(*(uint*)(thisGhost + 0x6c));  // Some cleanup/callback
        }
        // Copy another transform (position/velocity)
        srcPtr[0x1b] = *(undefined8*)(thisGhost + 0xd8);
        srcPtr[0x1c] = *(undefined8*)(thisGhost + 0xe0);
        srcPtr[0x1d] = *(undefined8*)(thisGhost + 0xe8);
        FUN_00757ab0((int*)(thisGhost + 0xc0));  // Some flag checker
        // Re-evaluate exiting condition
        if (((*(byte*)(thisGhost + 0xa8) & 1) == 0) ||
            (((*(int*)(thisGhost + 0xc0) == 0 || (*(int*)(thisGhost + 0xc0) == 0x48)) &&
             ((*(byte*)(thisGhost + 0xd4) & 1) == 0)))) {
            isExiting = false;
        } else {
            isExiting = true;
        }
        if (isExiting) {
            *(uint*)(srcPtr + 0x15) |= 1;  // Set bit 0 (exiting)
        } else {
            *(uint*)(srcPtr + 0x15) &= 0xfffffffe;
        }
        FUN_0075cd50(&stackVar2);  // Some cleanup
        // Set/clear animations flag (bit 2)
        if ((*(uint*)(thisGhost + 0xa8) >> 2 & 1) == 0) {
            *(uint*)(srcPtr + 0x15) &= 0xfffffffb;
        } else {
            *(uint*)(srcPtr + 0x15) |= 4;
        }
        // Copy main transform (translation, rotation, scale)
        srcPtr[0xf] = *(undefined8*)(thisGhost + 0x78);
        srcPtr[0x10] = *(undefined8*)(thisGhost + 0x80);
        srcPtr[0x11] = *(undefined8*)(thisGhost + 0x88);
        srcPtr[0x12] = *(undefined8*)(thisGhost + 0x90);
        srcPtr[0x13] = *(undefined8*)(thisGhost + 0x98);
        srcPtr[0x14] = *(undefined8*)(thisGhost + 0xa0);
        // Copy additional fields
        *(undefined4*)((int)srcPtr + 0xac) = *(undefined4*)(thisGhost + 0xac);
        *(undefined4*)((int)srcPtr + 0xbc) = *(undefined4*)(thisGhost + 0xbc);
        *(undefined4*)(srcPtr + 0x1e) = *(undefined4*)(thisGhost + 0xf0);
        // Set some flags based on source state
        if ((*(uint*)(thisGhost + 0xa8) >> 6 & 1) != 0) {
            *(uint*)(srcPtr + 0x15) |= 0x40;
        }
        // Toggle "isPassenger" flag? (bit 0x1a)
        if ((*(uint*)(thisGhost + 0xa8) >> 0x1a & 1) == 0) {
            *(uint*)(srcPtr + 0x15) |= 0x10000;
        } else {
            *(uint*)(thisGhost + 0xa8) &= 0xfbffffff;  // Clear bit 0x1a
        }
        // Debug or developer flags
        if (DAT_00e51966 != '\0') {
            *(uint*)(srcPtr + 0x15) |= 0x40000;
        }
        if (DAT_00e51965 != '\0') {
            *(uint*)(srcPtr + 0x15) |= 0x20000;
            return;
        }
    }
    return;
}