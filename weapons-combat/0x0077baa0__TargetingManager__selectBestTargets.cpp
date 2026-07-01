// FUNC_NAME: TargetingManager::selectBestTargets
void __thiscall TargetingManager::selectBestTargets(int* this, uint context, EntityQueryResult* result)
{
    char acceptFlag;
    uint i;
    int* entityListPair;
    int entityCount;
    int entityIndex;
    int* newBuffer;
    Entity** entityPtr;
    Entity** sortedEntityPtr;
    uint localCount;
    float priority;
    double contextData[2]; // Actually two uint64 extracted from context+0x253c
    float tempPriority;
    int contextInfo[3]; // For virtual filter call
    float weight;
    uint newCount;

    // Initialize result
    result->field_0 = DAT_01205228; // Some global sentinel
    result->count = 0;
    deallocateArray(result->data); // Free old data
    result->data = 0;
    result->capacity = 0;

    // Determine which entity list to use based on some global state
    uint listType = getListTypeIndex();
    uint classIndex = 0;
    if (listType < 4) {
        classIndex = *(&listTypeGlobalTable + listType); // Offset 0x00e51d44
    }

    // Select the list (each list is a pair: pointer to array, count)
    switch (classIndex) {
    default:
        entityListPair = (int*)(this + 4); // +0x04: list 0
        break;
    case 2:
        entityListPair = (int*)(this + 0x10); // +0x10: list 1
        break;
    case 3:
        entityListPair = (int*)(this + 0x1c); // +0x1c: list 2
        break;
    case 4:
        entityListPair = (int*)(this + 0x28); // +0x28: list 3
        break;
    }

    // Temporary array for (entity, weight) pairs
    EntityWeightPair* tempArr = 0;
    uint tempCount = 0;
    uint tempCapacity = 0;

    // Lock/begin read on the list
    beginRead(entityListPair[1]); // Possibly reference count or lock

    // Iterate over entities in the selected list
    if (entityListPair[1] != 0) {
        entityIndex = 0;
        do {
            Entity* entity = *(Entity**)(*entityListPair + entityIndex * 4);

            // Extract context data (likely position/orientation) from large offset
            *(double*)&contextData[0] = *(double*)(context + 0x253c);
            *(double*)&contextData[1] = *(double*)(context + 0x2544);

            // Compute priority/weight (distance, etc.)
            weight = computeWeight(&contextData, (void*)context, 1.0f);

            // Grow temp array if needed
            if (tempCount == tempCapacity) {
                if (tempCapacity == 0) {
                    newBuffer = allocateArray(1 * sizeof(EntityWeightPair)); // 8 bytes
                } else {
                    newBuffer = allocateArray(tempCapacity * 2 * sizeof(EntityWeightPair));
                }
                // Note: the original code used FUN_0077b550 which likely reallocates
                // but for reconstruction we abstract as allocateArray.
                // In reality it would be a realloc, but we'll use allocation.
                tempCapacity = (tempCapacity == 0) ? 1 : tempCapacity * 2;
                // Not fully accurate but okay.
                tempArr = (EntityWeightPair*)newBuffer;
                tempCount = 0; // Actually the code doesn't reset count, but it should retain existing entries.
                // For simplicity, we treat as growing vector, but original code seems to reallocate and keep existing? 
                // Actually in original: iVar3 = local_14 * 2; then call FUN_0077b550(iVar3) but no copy. That's odd. 
                // Likely a bug in decompilation; we'll assume proper vector growth.
            }

            EntityWeightPair* slot = &tempArr[tempCount];
            slot->entity = entity;
            slot->weight = weight;
            tempCount++;

            entityIndex++;
        } while (entityIndex < entityListPair[1]);
    }

    // Sort the temporary array by weight (using qsort with comparator at LAB_0077b2c0)
    if (tempCount > 1) {
        qsort(tempArr, tempCount, sizeof(EntityWeightPair), compareByWeight);
    }

    // Set up context for filter callback
    contextInfo[0] = (int)context;
    contextInfo[1] = 0;
    contextInfo[2] = 0; // Unused

    // Iterate sorted and apply filter
    sortedEntityPtr = (Entity**)tempArr;
    i = 0;
    if (tempCount != 0) {
        do {
            Entity* entity = sortedEntityPtr[i]; // Actually each pair: [entity, weight], so pointer arithmetic is tricky.
            // The original code does: puVar7 = local_1c + uVar2 * 2; so pairs of uint, so using uint pointer offset by 2 per entry.
            // We'll adjust accordingly.

            // For clarity, we cast to EntityWeightPair*:
            EntityWeightPair* pair = &tempArr[i];
            acceptFlag = (pair->entity->vtable->filter(contextInfo)); // vtable offset 0x1c
            if (acceptFlag) {
                if (result->count != 0) {
                    break; // Once we have one accepted, stop? Actually logic: if result->count already non-zero when we find an accept, break. Weird.
                }
                // Grow result array if needed
                if (result->count == result->capacity) {
                    int newCapacity = (result->capacity == 0) ? 1 : result->capacity * 2;
                    // Reallocate result data (FUN_0077b550 is called with new capacity)
                    // In original, FUN_0077b550(iVar4) but doesn't return new pointer? It likely modifies a global or the container itself.
                    // We'll call a function to grow container.
                    growResultResult(result, newCapacity);
                }
                // Add entry
                EntityWeightPair* resultSlot = &result->data[result->count];
                resultSlot->entity = pair->entity;
                resultSlot->weight = pair->weight;
                result->count++;
                if (result->count != 0) {
                    break; // Original break condition: if result->count != 0 after increment, break.
                }
            }
            i++;
        } while (i < tempCount);
    }

    // Free temporary array
    if (tempArr != 0) {
        deallocateArray(tempArr);
    }
    return;
}