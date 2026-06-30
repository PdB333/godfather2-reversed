// FUNC_NAME: ObjectNodeManager::findOrCreateNode
int ObjectNodeManager::findOrCreateNode(
    void* parentObj,                 // param1: parent object (+0x10 stored in node)
    uint typeMask,                   // param2: type mask stored at node+0x84
    uint flags,                      // param3: creation flags
    float transformData[16],         // param4: 4x4 transform matrix (16 floats) passed in EAX
    int id1,                         // param5: first ID (+0x70)
    int id2                          // param6: second ID (+0x74)
)
{
    int nodePtr;
    bool bVar2;
    bool bVar3;
    int *piVar10;

    // Check if parent object is valid and typeMask matches its capabilities
    if ((*(char *)((int)parentObj + 0x1c) != '\0') &&
        (uint bitmask = (*(code *)PTR_FUN_0110ac0c)(*(char *)((int)parentObj + 0x1d)); (typeMask & bitmask) != 0))
    {
        nodePtr = s_nodeListHead; // DAT_01205514
        // If parent object is marked +0x14 bit 3 or flags has 0x400, search existing nodes
        if (((*(byte *)((int)parentObj + 0x14) & 8) != 0) || ((flags & 0x400) != 0))
        {
            // Traverse linked list (node +0x10 = parentObj, +0x70 = id1, +0x74 = id2)
            for (; nodePtr != 0; nodePtr = *(int *)(nodePtr + 0x14))
            {
                if ((*(int *)(nodePtr + 0x10) != 0) && (*(int *)(nodePtr + 0x10) == (int)parentObj) &&
                    (*(int *)(nodePtr + 0x70) == id1) && (*(int *)(nodePtr + 0x74) == id2))
                {
                    // Node found; if it has a valid 'next' pointer? Actually +0x8 seems to be a pointer to pointer (maybe to store data?)
                    if (*(int *)(nodePtr + 8) == 0)
                    {
                        return nodePtr;  // Return existing node
                    }
                    // If there's something there, clear it (maybe a pending operation)
                    *(int *) (*(int *)(nodePtr + 8)) = 0;
                    *(int *)(nodePtr + 8) = 0;
                    return nodePtr;
                }
            }
            // If flags had 0x400 and we didn't find one, fail (return 0)
            if ((flags & 0x400) != 0)
            {
                return 0;
            }
        }

        // Allocate new node
        nodePtr = allocateNode(); // FUN_0051a1a0
        if (nodePtr != 0)
        {
            // Store IDs
            *(int *)(nodePtr + 0x74) = id2;
            *(int *)(nodePtr + 0x70) = id1;

            // Copy 16 floats from transformData to node at offset 0x30
            // transformData passed in EAX (parameter 4)
            for (int i = 0; i < 16; i++)
            {
                *(float *)(nodePtr + 0x30 + i*4) = transformData[i];
            }

            // Store typeMask
            *(uint *)(nodePtr + 0x84) = typeMask;

            // Initialize node (probably set up vtable/refcount)
            initializeNode(nodePtr); // FUN_0051d020

            // Call virtual function at offset 0x78 (e.g., onCreated)
            (**(code **)(nodePtr + 0x78))();

            // Set flag if flags has 4 (probably "persistent" or "important")
            if ((flags & 4) != 0)
            {
                *(uint *)(nodePtr + 0xc) |= 0x400000;
            }

            // If parent has a "high priority" flag, set flag in node
            if ((*(uint *)((int)parentObj + 0x14) & 0x20000000) != 0)
            {
                flags |= 1;
            }

            bVar3 = false;
            bVar2 = false;
            // Handle processing mode based on flags
            if ((flags & 2) == 0)
            {
                if ((flags & 1) == 0)
                {
                    // Neither flag: check if node can be processed, else delete
                    if ((*(uint *)((int)parentObj + 0x14) & 4) == 0)
                    {
                        char cVar7 = validateNode(nodePtr); // FUN_0051c200
                        if (cVar7 == '\0')
                        {
                            deleteNode(nodePtr); // FUN_0051a330
                            return 0;
                        }
                    }
                }
                else
                {
                    // flag 1: mark as active
                    *(uint *)(nodePtr + 0xc) |= 1;
                    if ((*(byte *)((int)parentObj + 0x14) & 4) == 0)
                    {
                        bVar3 = true;
                        bVar2 = true;
                    }
                }
            }
            else
            {
                // flag 2: also mark active, but no bVar2
                *(uint *)(nodePtr + 0xc) |= 1;
                bVar3 = true;
                bVar2 = false;
            }

            addToQueue(nodePtr); // FUN_0051a710

            // Find last node in list
            piVar10 = &s_nodeListHead; // DAT_01205514
            int iter = s_nodeListHead;
            while (iter != 0)
            {
                piVar10 = (int *)(iter + 0x14); // node->next
                iter = *piVar10;
            }
            // Insert at tail
            *(int *)(nodePtr + 0x14) = 0; // new tail's next is 0
            *piVar10 = nodePtr;

            // Additional scheduling if bVar2 set and not already scheduled
            if (bVar2 && ((*(uint *)(nodePtr + 0xc) & 0x40000) == 0))
            {
                *(uint *)(nodePtr + 0xc) |= 0x40000;
                scheduleUpdate(nodePtr); // FUN_0051b120
            }
            if (bVar3)
            {
                scheduleUpdate(nodePtr); // FUN_0051b120
            }

            // If active and parent has high priority flag, set a "high priority" bit
            if (((*(uint *)(nodePtr + 0xc) & 1) != 0) &&
                ((*(uint *)(*(int *)(nodePtr + 0x10) + 0x14) & 0x20000000) != 0))
            {
                *(uint *)(nodePtr + 0xc) |= 0x80000000;
            }

            // If both scheduled and active, and validation passes, run immediate update
            if (((*(uint *)(nodePtr + 0xc) & 0x40000) != 0) && ((*(uint *)(nodePtr + 0xc) & 1) != 0))
            {
                char cVar7 = validateNode(nodePtr); // FUN_0051c200
                if (cVar7 != '\0')
                {
                    runImmediateUpdate(nodePtr); // FUN_0051b210
                }
            }

            // If node is "signed" (high bit clear), clear active flag? Actually (int) >= 0 means high bit not set
            if ((int)*(uint *)(nodePtr + 0xc) >= 0)
            {
                *(uint *)(nodePtr + 0xc) &= 0xFFFFFFFE; // clear bit 0
            }

            // Logging if enabled
            if (s_loggingEnabled != '\0') // DAT_012054e8
            {
                logNode(nodePtr, s_logData); // FUN_0051abd0, DAT_01206800
            }

            return nodePtr;
        }
    }
    return 0;
}