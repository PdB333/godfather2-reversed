// FUNC_NAME: GhostManager::processGhostChanges
void __fastcall GhostManager::processGhostChanges( GhostManager* this )
{
    uint32_t* pHashNode;
    uint32_t* pNode;
    int result;
    char flag;
    uint32_t* pInput;
    int iBucketCount;
    uint32_t* pBucket;
    uint32_t uHash;
    uint32_t uID;
    uint32_t uNew;
    uint32_t* pNewIDs;
    uint32_t newIDCount;
    uint32_t* pID;
    int oldCount;

    // If any of the three pending counts are non-zero, post a "loading" message
    if ( this->pendingGhostCount != 0 || this->ghostCount != 0 || this->anotherGhostCount != 0 )
    {
        pInput = &this->field_0xbcc; // pointer to some data
        char loadingMsg[] = "Loading";
        bool error = false;
        FUN_00408a00( &loadingMsg, 0 ); // likely a log or push message
    }

    // Copy input data from in_EAX (first argument in EAX, fastcall with this)
    pInput = &this->field_0xbcc;
    if ( in_EAX == nullptr )
    {
        this->field_0xbd8 = 0;
        this->field_0xbd4 = 0;
        this->field_0xbd0 = 0;
        *pInput = 0;
    }
    else
    {
        *pInput = *in_EAX;
        this->field_0xbd0 = in_EAX[1];
        this->field_0xbd4 = in_EAX[2];
        this->field_0xbd8 = in_EAX[3];
    }

    GameManager* pGameManager = *(GameManager**)0x0122337c; // global singleton
    uint32_t entryIndex = 0;

    // First loop: remove ghosts that are already in the main array from the pending array
    if ( this->pendingEntryCount != 0 )
    {
        PendingEntry* pEntry = &this->pendingEntries[0]; // starting at offset 0x6d4, stride 40 bytes (10 ints)
        do
        {
            if ( pEntry->typeFlag == 0 )
            {
                // Type 0: hash from string
                pObject = nullptr;
                uint32_t* pBucket = &pGameManager->hashBuckets[0]; // some array
                uint32_t bucketIndex = 0;
                do
                {
                    if ( bucketIndex >= pGameManager->bucketCount )
                    {
                        if ( pObject == nullptr )
                        {
                            char* pString = (char*)pEntry->stringPtr;
                            if ( pString == nullptr )
                                pString = "Default";
                            uID = FUN_00405900( pString, 0 ); // hash string
                        }
                        break;
                    }
                    pObject = (Object*)FUN_004a8310( *pBucket );
                    bucketIndex++;
                    pBucket++;
                } while ( pObject == nullptr );
                uID = FUN_004059b0( *(uint32_t*)pObject ); // get ID from object
            }
            else
            {
                // Type non-zero: hash from 5 integer fields
                uID = FUN_004059b0( ((pEntry->field1 * 0x21 + pEntry->field2) * 0x21 + pEntry->field3) * 0x21 + pEntry->field4 );
            }

            if ( uID != 0 )
            {
                uint32_t j = 0;
                if ( this->ghostCount != 0 )
                {
                    do
                    {
                        if ( this->ghostIDs[j] == uID )
                        {
                            if ( (int)j >= 0 && j < this->ghostCount )
                            {
                                // Remove ID from array by shifting left
                                if ( j < this->ghostCount - 1 )
                                {
                                    do
                                    {
                                        this->ghostIDs[j] = this->ghostIDs[j+1];
                                        j++;
                                    } while ( j < this->ghostCount - 1 );
                                }
                                this->ghostCount--;
                            }
                            break;
                        }
                        j++;
                    } while ( j < this->ghostCount );
                }
            }

            pEntry++;
            entryIndex++;
        } while ( entryIndex < this->pendingEntryCount );
    }

    // Save old count for later comparison
    oldCount = this->ghostCount;

    // Process entries from the pending buffer again, this time adding new ghosts
    newIDCount = 0;
    entryIndex = 0;

    if ( this->pendingEntryCount != 0 )
    {
        PendingEntry* pEntry = &this->pendingEntries[0];
        do
        {
            if ( pEntry->typeFlag == 0 )
            {
                pObject = nullptr;
                uint32_t* pBucket = &pGameManager->hashBuckets[0];
                uint32_t bucketIndex = 0;
                do
                {
                    if ( bucketIndex >= pGameManager->bucketCount )
                    {
                        if ( pObject == nullptr )
                        {
                            char* pString = (char*)pEntry->stringPtr;
                            if ( pString == nullptr )
                                pString = "Default";
                            uID = FUN_00405900( pString, 0 );
                        }
                        break;
                    }
                    pObject = (Object*)FUN_004a8310( *pBucket );
                    bucketIndex++;
                    pBucket++;
                } while ( pObject == nullptr );
                uID = FUN_004059b0( *(uint32_t*)pObject );
            }
            else
            {
                uID = FUN_004059b0( ((pEntry->field1 * 0x21 + pEntry->field2) * 0x21 + pEntry->field3) * 0x21 + pEntry->field4 );
            }

            if ( uID == 0 )
            {
                // ID zero: try to allocate a new ghost slot
                result = FUN_00452590();
                if ( result < 0 )
                {
                    uID = this->pendingGhostCount; // slot index
                    if ( uID < 0x20 )
                    {
                        GhostBuffer* pBuffer = (GhostBuffer*)( (uint8_t*)this + 0x1c4 + uID * 0x28 );
                        this->pendingGhostCount = uID + 1;
                        pBuffer->typeFlag = pEntry->typeFlag;
                        pBuffer->field1 = pEntry->field1;
                        pBuffer->field2 = pEntry->field2;
                        pBuffer->field3 = pEntry->field3;
                        pBuffer->field4 = pEntry->field4;
                        FUN_004d3e20( pBuffer->stringPtr, pEntry->stringPtr ); // copy string
                        pBuffer->anotherFlag = pEntry->anotherFlag; // offset +0x24 from start of buffer
                    }
                }
            }
            else
            {
                // ID non-zero: collect new ghost IDs
                if ( newIDCount < 0x20 )
                {
                    newGhostIDs[newIDCount] = uID;
                    newIDCount++;
                }

                // Look up in hash table
                iBucketIndex = uID % pGameManager->hashTableSize;
                pHashNode = *(uint32_t**)( pGameManager->hashTable + iBucketIndex * 4 );
                while ( pHashNode != nullptr )
                {
                    if ( *pHashNode == uID )
                    {
                        if ( pHashNode != nullptr && pHashNode[1] != 0 )
                        {
                            result = *(int*)( pHashNode[1] + 0x24 ); // some status
                            goto foundStatus;
                        }
                        break;
                    }
                    pHashNode = (uint32_t*)pHashNode[2]; // next in chain
                }
                result = -1;
foundStatus:
                if ( result == -1 || result == 2 )
                {
                    // Need to allocate a new ghost
                    result = FUN_00452590();
                    if ( result < 0 )
                    {
                        uID = this->pendingGhostCount;
                        if ( uID < 0x20 )
                        {
                            GhostBuffer* pBuffer = (GhostBuffer*)( (uint8_t*)this + 0x1c4 + uID * 0x28 );
                            this->pendingGhostCount = uID + 1;
                            pBuffer->typeFlag = pEntry->typeFlag;
                            pBuffer->field1 = pEntry->field1;
                            pBuffer->field2 = pEntry->field2;
                            pBuffer->field3 = pEntry->field3;
                            pBuffer->field4 = pEntry->field4;
                            FUN_004d3e20( pBuffer->stringPtr, pEntry->stringPtr );
                            pBuffer->anotherFlag = pEntry->anotherFlag;
                        }
                    }
                }
                else if ( result == 4 )
                {
                    // Check if already in main ghost array
                    uNew = 0;
                    if ( this->ghostCount != 0 )
                    {
                        do
                        {
                            if ( this->ghostIDs[uNew] == uID )
                            {
                                if ( (int)uNew >= 0 )
                                    goto skipAdd;
                                break;
                            }
                            uNew++;
                        } while ( uNew < this->ghostCount );
                    }
                    // Add to main array if space
                    if ( this->ghostCount < 0x20 )
                    {
                        this->ghostIDs[this->ghostCount] = uID;
                        this->ghostCount++;
                    }
skipAdd:
                    // Now schedule a ghost update
                    result = FUN_00452590();
                    if ( result < 0 )
                    {
                        FUN_00452450();
                    }
                }
            }

            pEntry++;
            entryIndex++;
        } while ( entryIndex < this->pendingEntryCount );
    }

    // Add ghosts from the second array (offset 0x118) if not already present
    uint32_t k = 0;
    if ( this->secondGhostCount != 0 )
    {
        pID = &this->secondGhostIDs[0];
        do
        {
            uID = *pID;
            // Check new IDs
            uNew = 0;
            if ( newIDCount != 0 )
            {
                do
                {
                    if ( newGhostIDs[uNew] == uID )
                    {
                        if ( (int)uNew >= 0 )
                            goto foundInNew;
                        break;
                    }
                    uNew++;
                } while ( uNew < newIDCount );
            }
            // Check main array
            uNew = 0;
            if ( this->ghostCount != 0 )
            {
                do
                {
                    if ( this->ghostIDs[uNew] == uID )
                    {
                        if ( (int)uNew >= 0 )
                            goto foundInNew;
                        break;
                    }
                    uNew++;
                } while ( uNew < this->ghostCount );
            }
            // Not found, add to main array
            if ( this->ghostCount < 0x20 )
            {
                this->ghostIDs[this->ghostCount] = uID;
                this->ghostCount++;
            }
foundInNew:
            k++;
            pID++;
        } while ( k < this->secondGhostCount );
    }

    // Add ghosts from the third array (offset 0x118? Actually this appears to be another array at 0x118, but this is offset 0x198? Let's re-check: the code uses param_1+0x198 for count and param_1+0x118 for array)
    // Actually looking at decompiled: there is a loop with uVar10=0 and puVar12 = (uint *)(param_1 + 0x118); and count at param_1+0x198.
    uNew = 0;
    if ( this->thirdGhostCount != 0 )
    {
        pID = &this->thirdGhostIDs[0];
        do
        {
            uID = *pID;
            // Check new IDs
            uHash = 0;
            if ( newIDCount != 0 )
            {
                do
                {
                    if ( newGhostIDs[uHash] == uID )
                    {
                        if ( (int)uHash >= 0 )
                            goto foundInThird;
                        break;
                    }
                    uHash++;
                } while ( uHash < newIDCount );
            }
            // Check main array
            uHash = 0;
            if ( this->ghostCount != 0 )
            {
                do
                {
                    if ( this->ghostIDs[uHash] == uID )
                    {
                        if ( (int)uHash >= 0 )
                            goto foundInThird;
                        break;
                    }
                    uHash++;
                } while ( uHash < this->ghostCount );
            }
            // Not found, add to main array
            if ( this->ghostCount < 0x20 )
            {
                this->ghostIDs[this->ghostCount] = uID;
                this->ghostCount++;
            }
foundInThird:
            uNew++;
            pID++;
        } while ( uNew < this->thirdGhostCount );
    }

    // Remove ghosts from third array that are no longer in main array (newly added ones that exceed old count)
    int lastIndex = this->ghostCount - 1;
    if ( oldCount <= lastIndex )
    {
        pID = &this->ghostIDs[lastIndex];
        int countToRemove = lastIndex - oldCount + 1;
        do
        {
            uID = *pID;
            // Remove from third array if present
            uint32_t m = 0;
            if ( this->thirdGhostCount != 0 )
            {
                do
                {
                    if ( this->thirdGhostIDs[m] == uID )
                    {
                        if ( m < this->thirdGhostCount )
                        {
                            // Shift left
                            if ( m < this->thirdGhostCount - 1 )
                            {
                                do
                                {
                                    this->thirdGhostIDs[m] = this->thirdGhostIDs[m+1];
                                    m++;
                                } while ( m < this->thirdGhostCount - 1 );
                            }
                            this->thirdGhostCount--;
                        }
                        break;
                    }
                    m++;
                } while ( m < this->thirdGhostCount );
            }

            // Look up object in hash table and call FUN_004048c0 (likely free/return to pool)
            iBucketIndex = uID % pGameManager->hashTableSize;
            pHashNode = *(uint32_t**)( pGameManager->hashTable + iBucketIndex * 4 );
            while ( pHashNode != nullptr )
            {
                if ( *pHashNode == uID )
                {
                    if ( pHashNode != nullptr && pHashNode[1] != 0 )
                    {
                        FUN_004048c0( pHashNode[1], 0 ); // free object
                    }
                    break;
                }
                pHashNode = (uint32_t*)pHashNode[2];
            }

            pID--;
            countToRemove--;
        } while ( countToRemove != 0 );
    }

    // Remove ghosts from main array that are no longer valid (status != -1)
    int idx = this->ghostCount - 1;
    if ( idx >= 0 )
    {
        pID = &this->ghostIDs[idx];
        do
        {
            iBucketIndex = *pID % pGameManager->hashTableSize;
            pHashNode = *(uint32_t**)( pGameManager->hashTable + iBucketIndex * 4 );
            while ( pHashNode != nullptr )
            {
                if ( *pHashNode == *pID )
                {
                    if ( pHashNode != nullptr && pHashNode[1] != 0 && *(int*)( pHashNode[1] + 0x24 ) != -1 )
                        goto keepThisID;
                    break;
                }
                pHashNode = (uint32_t*)pHashNode[2];
            }
            // Not found or status == -1, remove from array
            if ( idx < this->ghostCount )
            {
                uint32_t shiftIdx = idx;
                if ( idx < this->ghostCount - 1 )
                {
                    do
                    {
                        this->ghostIDs[shiftIdx] = this->ghostIDs[shiftIdx+1];
                        shiftIdx++;
                    } while ( shiftIdx < this->ghostCount - 1 );
                }
                this->ghostCount--;
            }
keepThisID:
            pID--;
            idx--;
        } while ( idx >= 0 );
    }

    // Final condition: if no pending ghosts and no third ghosts, maybe log "Done" message
    if ( this->pendingGhostCount == 0 && this->thirdGhostCount == 0 )
    {
        if ( this->pendingEntryCount != 0 )
        {
            char doneMsg[] = "Done";
            bool error = false;
            pInput = &this->field_0xbcc;
            FUN_00408a00( &doneMsg, 0 );
            return;
        }
    }
    else
    {
        // If there are pending or third ghosts, and some global flag is set and check passes, increment a counter and send a network packet
        if ( *(uint32_t*)0x01206940 != 0 ) // global flag
        {
            char cVar4 = FUN_00402080( (char*)0x01206940 );
            if ( cVar4 == 0 )
            {
                *(uint32_t*)0x01206944 += 1;
                FUN_004084d0( 0x01206940, 0x8000 ); // send packet
            }
        }
        FUN_00452050(); // apply ghost updates
    }

    return;
}