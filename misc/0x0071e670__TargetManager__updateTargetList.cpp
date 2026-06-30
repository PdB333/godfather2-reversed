// FUNC_NAME: TargetManager::updateTargetList

bool __thiscall TargetManager::updateTargetList(void* this, bool shouldCheckVisibility)
{
    char alive;
    int entityIndex;
    int iVar3;
    uint objectIndex;
    int* objectListPtr;
    int* objectEntry;
    float distance;
    float priority;
    __m64 orientation[2]; // 8-byte each, likely a quaternion or m128

    // Get global sim manager and current player index
    iVar3 = gSimManager; // DAT_01129964
    entityIndex = getPlayerIndex(); // FUN_0077dd80
    objectListPtr = (int*)(iVar3 + 0x10 + entityIndex * 0xc);
    beginObjectIteration(); // FUN_0071dc20

    // Reset selection index to invalid
    *(int*)(this + 0x10) = -1;

    // Iterate over all objects in the global list
    if (objectListPtr[1] != 0) {
        objectIndex = 0;
        do {
            // Each object is stored as an int pointer at objectListPtr[0] + index*8
            int* objPtrRaw = *(int**)(*objectListPtr + objectIndex * 8);
            int* objBase = nullptr;
            if (objPtrRaw != nullptr) {
                objBase = objPtrRaw - 0x12; // offset -0x48, i.e., (int*)((char*)objPtrRaw - 0x48)
            }
            alive = isEntityAlive(*(void**)(this + 0xc)); // FUN_00727700
            if (alive != 0) {
                if (shouldCheckVisibility == false) {
                    // Directly check if the object can be targeted via vtable
                    alive = (*(code**)objBase)[7](*(void**)(this + 0xc)); // vtable+0x1c
                    if (alive != 0) goto addTarget;
                } else {
                    // Visibility check chain
                    alive = isEntityVisible(*(void**)(this + 0xc)); // FUN_00727450
                    if ((alive != 0) &&
                        (alive = isTargetInRange(objBase + 0x4c), alive != 0) && // FUN_0083e920
                        (alive = isSameTeam(*(void**)(this + 0xc), 0), alive == 0)) // FUN_007270a0
                    {
addTarget:
                        addObjectToList(objBase, 0); // FUN_0071dfc0
                    }
                }
            }
            objectIndex++;
        } while (objectIndex < (uint)objectListPtr[1]);
    }

    // Handle current target
    iVar3 = getCurrentTarget(); // FUN_0071e270
    if (iVar3 != 0) {
        clearTarget(iVar3); // FUN_0071d790
    }

    // Fetch orientation (two 8-byte components)
    *(int64*)&orientation[0] = *(int64*)(*(int*)(this + 0xc) + 0x253c);
    *(int64*)&orientation[1] = *(int64*)(*(int*)(this + 0xc) + 0x2544);

    // Update list of potential targets with distance priority
    if (*(int*)(this + 0x74) != 0) {
        objectListPtr = (int*)(this + 0x14); // start of target list (array of 3-int entries)
        do {
            int* targetBase = nullptr;
            if (*objectListPtr == 0) {
                targetBase = nullptr;
            } else {
                targetBase = *objectListPtr - 0x12; // offset -0x48
            }
            if (targetBase != (int*)iVar3) {
                alive = isTargetValid(*(void**)(this + 0xc)); // FUN_00726620
                if (alive != 0) {
                    // Calculate distance from orientation
                    distance = getFloatFromEntity(targetBase + 0x130); // FUN_004702b0
                    priority = calcPriority(&orientation, distance); // FUN_00726710
                    objectListPtr[2] = *(int*)&priority; // store priority
                } else {
                    *(int*)(this + 0x10) = -1;
                    updateTargetSlot(objectIndex); // FUN_0071ddd0
                }
            }
            objectIndex++;
            objectListPtr += 3;
        } while (objectIndex < *(uint*)(this + 0x74));
    }

    return iVar3 != 0;
}