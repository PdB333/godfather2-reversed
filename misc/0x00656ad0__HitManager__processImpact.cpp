// FUNC_NAME: HitManager::processImpact
void __thiscall HitManager::processImpact(HitManager* this, ImpactInfo* impact, BitstreamReader* bitstream)
{
    // this: HitManager with object count at +0x24 and object array at +0x2c
    // impact: 20-byte structure (2 shorts + 4 ints) describing a hit
    // bitstream: network data reader for optional effect creation

    int objectIndex = 0;
    int* objectPtr = null;
    int* tempPtr;
    short* searchPtr;
    int count;
    int i;
    int* refCount;
    byte bitField;
    undefined8* dest;
    undefined4* effectListPtr = null;
    char buffer[64]; // local buffer for temporary operations
    // ... more locals

    FUN_0064b9e0(0x40, buffer); // clear temporary buffer

    if (0 < this->objectCount) { // this+0x24
        do {
            objectPtr = this->objectArray[objectIndex]; // this+0x2c
            if (objectPtr[0x6d] == 2) { // state == waitingForImpact
                int flag = objectPtr[100]; // hasBeenHit?
                if ((char)flag == '\0') {
                    goto checkFlag;
                }
                else {
                    char isNetwork = FUN_006549b0(); // isNetworkSession
                    if (isNetwork == '\0') {
                        if ((char)flag == '\0') {
checkFlag:
                            isNetwork = FUN_006549b0();
                            if (isNetwork == '\0') {
                                // search existing impacts list
                                int impactCount = objectPtr[0x61]; // current stored impacts count
                                int* impactArrayBase = objectPtr[99]; // pointer to impact array
                                int j = 0;
                                if (0 < impactCount) {
                                    searchPtr = (short*)impactArrayBase;
                                    do {
                                        if ((impact->firstShort == searchPtr[0]) &&
                                            (impact->secondShort == searchPtr[1]) &&
                                            (impact->firstInt == *(int*)(searchPtr + 2)) &&
                                            (impact->secondInt == *(int*)(searchPtr + 4)) &&
                                            (impact->thirdInt == *(int*)(searchPtr + 6)) &&
                                            (impact->fourthInt == *(int*)(searchPtr + 8))) {
                                            break;
                                        }
                                        j++;
                                        searchPtr += 10; // each impact is 20 bytes (10 shorts)
                                    } while (j < impactCount);
                                }
                                if (j == impactCount) {
                                    // not found, check if second tier match
                                    j = 0;
                                    if (0 < impactCount) {
                                        searchPtr = (short*)impactArrayBase;
                                        do {
                                            if ((impact->firstShort == searchPtr[0]) &&
                                                (impact->firstInt == *(int*)(searchPtr + 2)) &&
                                                (impact->secondInt == *(int*)(searchPtr + 4)) &&
                                                (impact->thirdInt == *(int*)(searchPtr + 6)) &&
                                                (impact->fourthInt == *(int*)(searchPtr + 8))) {
                                                break;
                                            }
                                            j++;
                                            searchPtr += 10;
                                        } while (j < impactCount);
                                    }
                                    if (j == impactCount) {
                                        goto nextObject; // impact not relevant
                                    }
                                    if (impactCount < 5) {
                                        FUN_00654620(); // something to prepare for append
                                        objectPtr[0x61] = objectPtr[0x61] + 1;
                                        dest = (undefined8*)(objectPtr[99] - 0x14 + objectPtr[0x61] * 0x14);
                                        if (dest != null) {
                                            dest[0] = *(undefined8*)impact;
                                            dest[1] = *(undefined8*)(&impact->firstInt);
                                            dest[2] = *(undefined4*)(&impact->fourthInt);
                                        }
                                    }
                                }
                                if ((char)objectPtr[100] != '\0') break;
                            }
                        }
                    }
                }
            }
nextObject:
            objectIndex++;
        } while (objectIndex < this->objectCount);
    }

    if (objectIndex == this->objectCount) {
        return; // no matching object found
    }

    // we have a valid object and impact, now process network data
    FUN_0065a5e0(local_278); // initialize something from local buffer
    char valid = FUN_0064ca10(bitstream, local_278); // read alignment or check
    if (valid == '\0') {
        // cleanup linked list
        while (effectListPtr != null) {
            int* next = (int*)effectListPtr[2];
            effectListPtr[0] = 0;
            effectListPtr[1] = 0;
            effectListPtr[2] = 0;
            effectListPtr = next;
        }
        goto cleanup;
    }

    FUN_0064b9e0(0x40, local_2a0); // clear another temporary buffer
    char isNetwork = FUN_006549b0();
    if (isNetwork != '\0') {
        // cleanup again
        while (effectListPtr != null) {
            int* next = (int*)effectListPtr[2];
            effectListPtr[0] = 0;
            effectListPtr[1] = 0;
            effectListPtr[2] = 0;
            effectListPtr = next;
        }
        goto cleanup;
    }

    int bitPos = bitstream->currentBit; // +0x18
    if (bitstream->totalBits < bitPos) {
        bitstream->overflowFlag = 1; // +0x1c
    }
    else {
        byte* data = bitstream->data; // +0xc
        bitField = data[bitPos >> 3];
        bitstream->currentBit = bitPos + 1;
        if ((bitField & (1 << (bitPos & 7))) != 0) {
            char isPlayerHit = FUN_0046d790(); // player-specific?
            if (isPlayerHit == '\0') {
                // create decal effect (0x24 bytes)
                int* decal = (int*)FUN_009c8e50(0x24);
                if (decal != 0) {
                    decal = FUN_00654840(bitstream);
                }
                // reference counting for previous effect
                int* prevDecal = objectPtr[0x54];
                if (prevDecal != null) {
                    refCount = prevDecal + 2;
                    *refCount = *refCount - 1;
                    if (*refCount == 0) {
                        (**(code**)(*prevDecal + 8))(); // destructor via vtable
                    }
                }
                objectPtr[0x54] = decal;
                if (decal != null) {
                    decal[2] = decal[2] + 1; // increment ref count
                }
                int newDecal = objectPtr[0x54];
                if ((*(char*)(newDecal + 0x20) != '\0') &&
                    (isNetwork = (**(code**)(*objectPtr + 0x1c))(newDecal, 1), isNetwork != '\0')) {
                    goto handleSuccess;
                }
            }
            else {
                // create projectile effect (0x2c bytes)
                int* proj = (int*)FUN_009c8e50(0x2c);
                if (proj != 0) {
                    proj = FUN_00654ad0(bitstream);
                }
                int* prevProj = objectPtr[0x56];
                if (prevProj != null) {
                    refCount = prevProj + 2;
                    *refCount = *refCount - 1;
                    if (*refCount == 0) {
                        (**(code**)(*prevProj + 8))();
                    }
                }
                objectPtr[0x56] = proj;
                if (proj != null) {
                    proj[2] = proj[2] + 1;
                }
                if ((*(char*)(objectPtr[0x56] + 0x24) != '\0') &&
                    (isNetwork = (**(code**)(*objectPtr + 0x18))(objectPtr[0x56], 1), isNetwork != '\0')) {
                    int* effectData = *(int**)(objectPtr[0x56] + 0x18);
                    if (effectData != null) {
                        effectData[2] = effectData[2] + 1;
                    }
                    local_2a0[0] = effectData;
                    FUN_00657960(); // some processing
                    if (effectData != null) {
                        refCount = effectData + 2;
                        *refCount = *refCount - 1;
                        if (*refCount == 0) {
                            (**(code**)(*effectData + 8))();
                        }
                    }
handleSuccess:
                    // update manager state
                    if ((this->managerRef == 0) || // this+0x30
                        (*(int*)(this->managerRef + 0x10) != *(int*)((*objectPtr[0x54]) + 0x10))) {
                        int* newObj = FUN_009c8e50(0x24);
                        if (newObj != 0) {
                            FUN_0065e100(*(undefined4*)(*objectPtr[0x54] + 0x10));
                        }
                        FUN_00657990(); // alternate path
                    }
                    else {
                        FUN_00657960(); // same path as above
                    }
                    FUN_0065e570(objectPtr[0x55], local_2a0, *objectPtr[0x54]);
                    FUN_006544b0(); // flush effects?
                    if ((local_2a0[0] != null) &&
                        (local_2a0[0][2] = local_2a0[0][2] - 1, local_2a0[0][2] == 0)) {
                        (**(code**)(*local_2a0[0] + 8))();
                    }
                    FUN_0065bf00((int)objectPtr + 0x162, 0x10); // clear some part
                    *(char*)((int)objectPtr + 0x131) = 1; // set some flag
                    goto copyImpact;
                }
            }
            // failure paths lead to cleanup
            FUN_00656aa0(); // fallback processing
            goto cleanup;
        }
    }
copyImpact:
    // store the impact data into the object
    *(undefined8*)(objectPtr + 0x40) = *(undefined8*)impact;
    *(undefined8*)(objectPtr + 0x42) = *(undefined8*)(&impact->firstInt);
    objectPtr[0x44] = impact->fourthInt; // last int
    objectPtr[0x6d] = 4; // state = processed
    objectPtr[0x67] = 0; // clear some counter
    objectPtr[0x68] = this->someTimer; // this+100 (0x64)
    FUN_00656fc0(this); // mark object as dirty for network replication

    // cleanup linked list
    while (effectListPtr != null) {
        int* next = (int*)effectListPtr[2];
        effectListPtr[0] = 0;
        effectListPtr[1] = 0;
        effectListPtr[2] = 0;
        effectListPtr = next;
    }
cleanup:
    FUN_0064b440(); // release temporary resources
    return;
}