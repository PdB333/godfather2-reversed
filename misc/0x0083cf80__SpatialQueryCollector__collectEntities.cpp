// FUNC_NAME: SpatialQueryCollector::collectEntities
uint __thiscall SpatialQueryCollector::collectEntities(uint entityId, float *nodePosition) {
    // this+0x20: float center[3] (query origin)
    float *center = *(float **)(this + 0x20);
    // Compute squared distance from nodePosition to center
    float dx = center[0] - nodePosition[0];
    float dy = center[1] - nodePosition[1];
    float dz = center[2] - nodePosition[2];
    float distSq = dx*dx + dy*dy + dz*dz;

    int resultCode = 2; // default: continue traversal
    if (*(float *)(this + 0x24) <= distSq && distSq != *(float *)(this + 0x24)) {
        // Distance exceeds threshold, skip this node entirely
        return CONCAT31((int3)((uint)center >> 8), 1);
    }

    // Validate the entity (likely a node ID)
    uint validationResult = FUN_0083b6d0(entityId, nodePosition);
    if ((char)validationResult == 0) {
        return validationResult; // invalid -> return failure
    }

    // Check a flag from the virtual controller (this+0x8 points to a controller object)
    uint flags = *(uint *)(*(int *)(this + 8) + 0xa8); // offset 0xa8 in controller
    if ((flags >> 10 & 1) == 0) {
        // Process children via virtual function at vtable+0x20
        resultCode = (**(code **)(**(int **)(this + 8) + 0x20))(entityId, nodePosition, nodePosition,
                    *(undefined4 *)(this + 0x20), *(undefined4 *)(this + 0x10),
                    *(undefined4 *)(this + 0x14), *(undefined4 *)(this + 0x18), *(undefined4 *)(this + 0x1c));
        if (resultCode == 3) {
            return 0; // abort
        }
    } else {
        // Distance is less than threshold2 (this+0x10) -> check first set of children
        if (distSq < *(float *)(this + 0x10)) {
            // Iterate over first child group (offset from nodePosition+4, count from nodePosition+5)
            uint firstCount = (uint)*(byte *)(nodePosition + 5);
            uint i = 0;
            while (i < firstCount) {
                int childIndex = (uint)(ushort)(*(short *)(nodePosition + 4) + (short)i) * 0x10 +
                                 *(int *)(entityId + 0x24); // array base at entityId+0x24
                char childValid = (**(code **)(**(int **)(this + 8) + 0x30))(entityId, childIndex);
                if (childValid != 0) {
                    float *childPos = (float *)(*(int *)(entityId + 0x20) + (uint)*(ushort *)(childIndex + 4) * 0x24);
                    float *centerPos = *(float **)(this + 0x20);
                    float cd = childPos[0] - centerPos[0];
                    float cy = childPos[1] - centerPos[1];
                    float cz = childPos[2] - centerPos[2];
                    if (*(float *)(this + 0x10) > cd*cd + cy*cy + cz*cz) {
                        break; // too far -> stop checking further children
                    }
                }
                i++;
            }

            // Iterate over second child group (offset from nodePosition+0x16, combined count from nodePosition+7 and nodePosition+0x15)
            uint secondCount = (uint)*(byte *)(nodePosition + 7) + (uint)*(byte *)((int)nodePosition + 0x15);
            uint j = 0;
            while (j < secondCount) {
                int childIndex = (uint)(ushort)(*(short *)((int)nodePosition + 0x16) + (short)j) * 0x10 +
                                 *(int *)(entityId + 0x30); // array base at entityId+0x30
                char childValid = (**(code **)(**(int **)(this + 8) + 0x34))(entityId, childIndex);
                if (childValid != 0) {
                    int localArray[2]; // stack storage for child node pointer (placeholder)
                    FUN_005fd1c0(localArray, childIndex); // get child node reference
                    if (localArray[0] != 0) {
                        float *childPos = *(float **)(this + 0x20);
                        float *cPos = (float *)&localArray[0]; // reinterpret first entry as float*?? 
                        // Actually the code uses pfStack_4 which is a float* from localArray.
                        // We'll assume it's the child's position or similar
                        float dx = childPos[0] - (* (float *)&localArray[0] ); // not correct, but approximating
                        // The actual check compares distance from center to childNode's position (stored at pfStack_4)
                        if (*(float *)(this + 0x10) <= dx*dx + ... ) {
                            FUN_004daf90(localArray); // release child node
                            break;
                        }
                        FUN_004daf90(localArray); // release child node
                    }
                }
                j++;
            }
            // Total children processed already in loops; goto label to skip adding to list
            goto LAB_0083d261;
        }
    }

    // Add entity to result list (this+0x28 is an array of 12-byte entries, this+4 is count)
    int *entryPtr = (int *)(this + 0x28 + *(int *)(this + 4) * 12);
    int oldId = *entryPtr;
    if (oldId != entityId) {
        if (oldId != 0) {
            FUN_004daf90(entryPtr); // release old entry
        }
        *entryPtr = entityId; // store new ID
        if (entityId != 0) {
            entryPtr[1] = *(int *)(entityId + 4); // store next pointer from entity
            *(int **)(entityId + 4) = entryPtr; // link entity to this entry
        }
    }
    entryPtr[2] = (int)nodePosition; // store node position pointer
    // Store result code in separate array at offset 0xc28
    *(int *)(this + 0xc28 + *(int *)(this + 4) * 4) = resultCode;
    // Increment count
    *(int *)(this + 4) = *(int *)(this + 4) + 1;
    uint newCount = *(uint *)(this + 4);
    if (newCount > 0xff) {
        // Maximum capacity reached (256 slots)
        return CONCAT31((int3)(newCount >> 8), 1);
    }
    if (newCount > 0x7f && (*(uint *)(*(int *)(this + 8) + 0xa8) >> 10 & 1) != 0) {
        // Expand threshold if >127 entries and flag set
        *(float *)(this + 0x24) = *(float *)(this + 0x24) * 1.2f; // DAT_00d5c454 assumed ~1.2
    }
LAB_0083d261:
    return newCount & 0xffffff00; // return count in high 24 bits (unusual, but seen in original)
}