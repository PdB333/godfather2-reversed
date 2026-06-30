// FUNC_NAME: PathFollower::advanceAlongPath
int __fastcall PathFollower::advanceAlongPath(PathFollower* this) {
    // Get the path node array pointer from this+0x10c
    PathNodeArray* nodeArray = *(PathNodeArray**)((char*)this + 0x10c);
    // Get number of nodes via vtable at offset 8
    int nodeCount = nodeArray->vtable->getNodeCount();
    // Get the last node at index count-1 via vtable at offset 0xc
    PathNode* lastNode = (PathNode*)nodeArray->vtable->getNode(nodeCount - 1);
    
    if (lastNode->isValid != 0) {
        // Current position (this+0x60 x,y, this+0x68 z)
        Vec3 currentPos;
        currentPos.x = *(float*)((char*)this + 0x60);
        currentPos.y = *(float*)((char*)this + 0x64);
        currentPos.z = *(float*)((char*)this + 0x68);
        
        // Get the node's position from its offset 0x00 (x,y) and 0x08 (z) [float* casting]
        Vec3 nodePos;
        nodePos.x = *(float*)((char*)lastNode + 0x00); // Actually lastNode[2]? Let's see: piVar4[2] is a float* meaning the third element? Wait, piVar4 is int* but then cast to float* for pfVar1. piVar4[2] is the third int, which is a pointer to float array? It's confusing. Let's re-read.
        // Actually piVar4 = (int*)(...)(iVar3+-1); piVar4 points to first int of node struct.
        // pfVar1 = (float*)piVar4[2]; -> piVar4[2] is the third int field (offset 8) which is a pointer to a float array (position?). But then they use *pfVar1, pfVar1[1], pfVar1[2] for x,y,z.
        // So the node struct has an int isValid at offset 0, something at offset 4? Then at offset 8 a pointer to Vec3? Or is it actually a Vec3 embedded? piVar4[2] could be a pointer.
        
        // Let's correct: piVar4 points to the start of node struct. piVar4[0] = isValid flag. piVar4[1] = unknown? piVar4[2] = pointer to float array (position). So nodePos = *(Vec3*)piVar4[2].
        Vec3* nodePosPtr = (Vec3*)lastNode->positionPtr; // assuming field at offset 8
        Vec3 nodePos = *nodePosPtr;
        
        // Get NavManager instance (returns a global singleton)
        NavManager* navMgr = (NavManager*)FUN_00471610(); // might be static
        // destination position from nav manager (offsets 0x30,0x34,0x38)
        Vec3 navDest;
        navDest.x = *(float*)((char*)navMgr + 0x30);
        navDest.y = *(float*)((char*)navMgr + 0x34);
        navDest.z = *(float*)((char*)navMgr + 0x38);
        
        // Compute dot product: (current - nodePos) · (nodePos - navDest)
        Vec3 diff1 = currentPos - nodePos;
        Vec3 diff2 = nodePos - navDest;
        float dot = diff1.x * diff2.x + diff1.y * diff2.y + diff1.z * diff2.z;
        
        // If dot < 0, we are past the node (or need to advance)
        if (dot < 0.0f) {
            // Get node count again (can reuse)
            nodeCount = nodeArray->vtable->getNodeCount();
            if (nodeCount > 1) {
                // Get previous node (index count-2)
                PathNode* prevNode = (PathNode*)nodeArray->vtable->getNode(nodeCount - 2);
                // Check if previous node is different from last node
                if (prevNode->isValid != lastNode->isValid || 
                    (prevNode->isValid != 0 && prevNode->positionPtr != lastNode->positionPtr)) {
                    // Something about projection or sliding
                    Vec3 projection; // local variable at stack
                    // Call FUN_005f5cb0 - likely pointOnSegment or project onto edge
                    bool success = FUN_005f5cb0(&projection, /* something */);
                    if (success) {
                        // Get the third float from nodePosPtr offset 0x0c (maybe radius or heading)?
                        float extraFloat = nodePosPtr[3]; // nodePosPtr is actually a float array with 4 elements? Or is it a pointer to struct with +0x0c being something.
                        // Actually pfStack_14 was set to pfVar1, then pfStack_14 = (float*)pfStack_14[3]; meaning pfVar1[3] is a pointer? Or float? Let's see: uStack_18 = uRam0000000c; pfStack_14 = (float*)pfStack_14[3];
                        // This suggests pfVar1 points to an array of floats where index 3 is a pointer (maybe another Vec3).
                        // Then it gets navMgr again, gets something at offsets 0x10,0x14,0x18 (a vector).
                        Vec3 navVec;
                        navVec.x = *(float*)((char*)navMgr + 0x10);
                        navVec.y = *(float*)((char*)navMgr + 0x14);
                        navVec.z = *(float*)((char*)navMgr + 0x18);
                        // FUN_0043a210 - likely normalize or cross product? Actually it takes &uStack_10 twice, so maybe it modifies in place. Given it's called with &navVec, &navVec, it might be a self-normalize.
                        FUN_0043a210(&navVec, &navVec); // maybe normalize(navVec);
                        // Call FUN_00756fc0 - move entity towards target? Parameters: currentPos pointer, something, pfStack_14 (the pointer from extra), &navVec
                        bool moved = FUN_00756fc0(&currentPos, projection, (void*)extraFloat, &navVec);
                        if (moved) {
                            return 1;
                        }
                    }
                }
            }
            // Teleport directly to node position (FUN_009a77c0) with entity handle at this+0x58
            int entityHandle = *(int*)((char*)this + 0x58);
            return FUN_009a77c0(entityHandle, &currentPos);
        }
    }
    return 0;
}