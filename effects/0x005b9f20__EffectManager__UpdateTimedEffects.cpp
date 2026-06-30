// FUNC_NAME: EffectManager::UpdateTimedEffects

void __thiscall EffectManager::UpdateTimedEffects(int* thisObj, int deltaTime, int context)
{
    int bucketIndex;
    int entryIndex;
    int* bucketCount;
    int* entryArray;
    int** entryPtrArray;
    int* entryStruct;
    int* innerArray;
    int innerCount;
    int innerIndex;
    int* innerEntryPtr;
    int innerField;
    int* fieldPtr;

    int totalDelta = deltaTime; // save delta time for global decrements
    bucketIndex = 0;
    if (0 < thisObj[0]) { // numBuckets > 0
        do {
            entryIndex = 0;
            if (0 < *(int*)(thisObj[1] + bucketIndex * 8)) { // entryCount for this bucket > 0
                do {
                    entryStruct = *(int**)(*(int*)(thisObj[1] + 4 + bucketIndex * 8) + entryIndex * 4);
                    switch(*entryStruct) { // type field at offset 0
                    case 1: // PersistentTimer
                        // Call global timer tick
                        FUN_005ac340(totalDelta, 0, context);
                        entryArray = *(int**)(thisObj[1] + 4 + bucketIndex * 8);
                        if (*(int*)(entryArray[entryIndex] + 4) != 0) {
                            *(int*)(entryArray[entryIndex] + 4) = *(int*)(entryArray[entryIndex] + 4) - totalDelta;
                        }
                        break;
                    case 2: // ConditionalTimer
                        if (entryStruct[1] != 0) { // offset 4 is nonzero
                            entryArray = *(int**)(thisObj[1] + 4 + bucketIndex * 8);
                            // Decrement offset 4 of entry
                            *(int*)(entryArray[entryIndex] + 4) = *(int*)(entryArray[entryIndex] + 4) - totalDelta;
                        }
                        break;
                    case 3: // CompoundTimer
                        innerArray = (int*)entryStruct[0xf]; // offset 0x3c (15*4)
                        if (innerArray != (int*)0x0) {
                            innerCount = 0;
                            if (0 < *innerArray) {
                                innerIndex = 0;
                                do {
                                    FUN_005ac340(totalDelta, 0, context);
                                    innerEntryPtr = (int*)(innerArray[1] + 8 + innerIndex); // stride 0xC
                                    innerField = *innerEntryPtr;
                                    if (innerField != 0) {
                                        *innerEntryPtr = innerField - totalDelta;
                                    }
                                    innerCount = innerCount + 1;
                                    innerIndex = innerIndex + 0xc;
                                } while (innerCount < *innerArray);
                            }
                            if (innerArray[1] != 0) {
                                innerArray[1] = innerArray[1] - totalDelta;
                            }
                        }
                        // Decrement offset 0x34 and 0x3c of the main entry
                        entryArray = *(int**)(thisObj[1] + 4 + bucketIndex * 8);
                        if (*(int*)(entryArray[entryIndex] + 0x34) != 0) {
                            *(int*)(entryArray[entryIndex] + 0x34) = *(int*)(entryArray[entryIndex] + 0x34) - totalDelta;
                        }
                        entryArray = *(int**)(thisObj[1] + 4 + bucketIndex * 8);
                        if (*(int*)(entryArray[entryIndex] + 0x3c) != 0) {
                            *(int*)(entryArray[entryIndex] + 0x3c) = *(int*)(entryArray[entryIndex] + 0x3c) - totalDelta;
                        }
                        break;
                    case 8: // SingleTimer
                        FUN_005ac340(totalDelta, 0, context);
                        entryArray = *(int**)(thisObj[1] + 4 + bucketIndex * 8);
                        if (*(int*)(entryArray[entryIndex] + 8) != 0) { // offset 8
                            *(int*)(entryArray[entryIndex] + 8) = *(int*)(entryArray[entryIndex] + 8) - totalDelta;
                        }
                        break;
                    }
                    // Post-switch: decrement the pointer value itself? (suspect decompilation artifact)
                    entryArray = *(int**)(thisObj[1] + 4 + bucketIndex * 8);
                    if (entryArray[entryIndex] != 0) {
                        entryArray[entryIndex] = (int*)((int)entryArray[entryIndex] - totalDelta);
                    }
                    entryIndex++;
                } while (entryIndex < *(int*)(thisObj[1] + bucketIndex * 8));
            }
            // Decrement the entry array pointer for this bucket
            entryArray = *(int**)(thisObj[1] + 4 + bucketIndex * 8);
            if (entryArray != 0) {
                *(int*)(thisObj[1] + 4 + bucketIndex * 8) = (int)entryArray - totalDelta;
            }
            bucketIndex++;
        } while (bucketIndex < thisObj[0]);
    }
    // Decrement the bucket array pointer
    if (thisObj[1] != 0) {
        thisObj[1] = (int)thisObj[1] - totalDelta;
    }
    // Free the data pointer
    int* dataPtr = (int*)thisObj[2];
    if (dataPtr != 0) {
        FUN_005ba710(); // cleanup function
        (*DAT_0119caf8)(dataPtr, 0x48); // custom deallocation (size 0x48)
    }
    thisObj[2] = 0; // nullify pointer
    return;
}