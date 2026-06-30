// FUNC_NAME: ActorTracker::handleSpawnMessage
void __thiscall ActorTracker::handleSpawnMessage(int thisPtr, int *messagePtr)
{
    // messagePtr points to { messageID (int), dataPtr (int*) }
    const int cMessageID = DAT_0120678c; // global message identifier for "spawn actor"
    if (*messagePtr != cMessageID) {
        return;
    }

    // Extract the target class ID from the message data
    int classInfoPtr = *(messagePtr + 1); // dataPtr
    int classID;
    if (*(int *)(classInfoPtr + 0xc) == 0) {
        classID = 0;
    } else {
        classID = *(int *)(*(int *)(classInfoPtr + 0xc) + 0x1c);
    }

    int *trackedArray = (int *)(thisPtr + 0x14); // +0x14: array of tracked entity IDs (max 0x20)
    uint trackedCount = *(uint *)(thisPtr + 0x94); // +0x94: current count

    // Check if this classID is already being tracked
    uint index = 0;
    if (trackedCount != 0) {
        while (trackedArray[index] != classID) {
            index++;
            if (trackedCount <= index) {
                return; // not found, nothing to update
            }
        }
    }

    // Found existing tracking for this class; proceed to add all matching entities
    if ((int)index < 0) {
        return; // sanity check
    }

    // Begin critical section or class iteration
    FUN_00411f20(); // likely lock or begin iteration

    // Global game manager singleton
    int *gameMgr = DAT_0122337c; // +0x50: hash table base, +0x54: hash table size, +0x6C: class list start

    // Vtable table for class hierarchy traversal (static)
    void **classVtblTable = PTR_DAT_00e2f0c4; // array of vtable pointers

    // Start with the class object corresponding to classID
    int iterState = 0;
    int iterIndex = 0;

    int classObjectPtr = FUN_004025a0(classID); // GetClassObjectByID (returns pointer to class descriptor)
    int currentClassVtbl = 0;
    int currentIsValid = 0;

    if (classObjectPtr != 0 && *(int *)(classObjectPtr + 0x18) != 0) {
        // classObjectPtr+0x18 points to vtable? Actually +0x18 might be vtable pointer for the class
        int classVtbl = *(int *)(classObjectPtr + 0x18);
        classVtblTable[0] = (void*)classVtbl; // store as first entry? Actually the code uses local_50[0] later
        iterState = 1;
        currentIsValid = 1;
    }

    while (currentIsValid != 0) {
        // Try to get the vtable from the current class using hash table lookup
        int hashEntry = *(int *)(gameMgr + 0x80); // +0x80: maybe direct class hash? but then fallback to list
        if (hashEntry != 0 && *(int *)(hashEntry + 0x2c) == *(int *)classVtblTable[currentIsValid]) {
            // Found via direct hash
            currentClassVtbl = hashEntry;
        } else {
            // Iterate through class list (linked list) starting at +0x6C
            for (int node = *(int *)(gameMgr + 0x6C); node != 0; node = *(int *)(node + 4)) {
                if (*(int *)(node + 0x2c) == *(int *)classVtblTable[currentIsValid]) {
                    currentClassVtbl = node;
                    goto foundVtbl;
                }
            }
            currentIsValid = 0;
            continue;
        }
foundVtbl:
        // Get the derived class ID from the vtable node
        int derivedClassID = *(int *)(currentClassVtbl + 0x1c);
        if (derivedClassID == classID) {
            // same class as requested, continue traversal
        } else {
            // Get object by derived class ID
            int derivedObj = FUN_004025a0(derivedClassID);
            int idValue;
            if (derivedObj == 0) {
                idValue = 0xfe16702f; // default ID (maybe invalid)
            } else {
                idValue = *(int *)(derivedObj + 0x2c); // +0x2c: actual object ID
            }
            // idValue is now used for hash table lookup of all instances
        }

        // Below: iterate through hash table to find all instances of this ID
        // This part is messy in decompiled; the logic appears to be:
        // - For each ID that is not already tracked, if the instance has certain flags, add it
        // The code has a goto pattern that loops:
        uint idValue = ...; // from derived class or fallback
loop_start:
        uint newID = FUN_00405a20(idValue); // Get actual entity ID from handle? Or hash?
        if (newID != 0) {
            uint j = 0;
            if (trackedCount != 0) {
                do {
                    if (trackedArray[j] == newID) {
                        if ((int)j >= 0) {
                            goto loop_start; // already tracked, skip
                        }
                        break;
                    }
                    j++;
                } while (j < trackedCount);
            }
            // Search the global hash table for this ID
            uint hashSlot = newID % *(uint *)(gameMgr + 0x54);
            uint *hashBucket = *(uint **)(*(int *)(gameMgr + 0x50) + hashSlot * 4);
            for (uint *entry = hashBucket; entry != 0; entry = (uint *)entry[2]) {
                if (*entry == newID) {
                    if (entry != 0 && entry[1] != 0 && *(int *)(entry[1] + 0x60) >= 0) {
                        // Valid entity with a flag (maybe alive)
                        int entityPtr = FUN_004025a0(newID); // get entity by ID
                        if (entityPtr != 0) {
                            FUN_00402920(entityPtr + 0x56, 0x100); // maybe clear a flag or set something
                        }
                        if (trackedCount < 0x20) {
                            trackedArray[trackedCount] = newID;
                            *(int *)(thisPtr + 0x94) = trackedCount + 1;
                        }
                    }
                    break;
                }
            }
            goto loop_start; // continue to next derived class? Actually this loops forever
        }
        // After processing, call next level in class hierarchy
        void (*nextClassFn)() = (void (*)())classVtblTable[1];
        nextClassFn();
        // Continue loop with next entry (after possible recursion)
        // Actually the while loop continues based on iterState
    } // end while

    // After adding entities, check flags
    uint flags = *(uint *)(thisPtr + 0x10); // +0x10: internal flags
    if ((flags & 1) != 0 && *(int *)(thisPtr + 0x94) == 0) {
        if ((flags & 0x10) != 0) {
            *(uint *)(thisPtr + 0x10) = flags & 0xfffffffe; // clear bit 0
            // Play some sound or trigger event using global constant
            FUN_00408a00((int *)(&DAT_01206a20), 0); // maybe stop tracking
            return;
        }
        *(uint *)(thisPtr + 0x10) = flags | 4; // set bit 2 (maybe "waiting for spawn")
    }
}
```