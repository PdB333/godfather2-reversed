// FUNC_NAME: Player::checkObjectiveTrigger
// Address: 0x00885a90
// Purpose: Checks if a trigger condition (hash 0x55859efa) is met and plays an associated audio event.
// The function registers a sub-object (from this+0x50) into a linked list stored at this+0x58+0x1e90.
// Then queries a target component and validates it against a hash; if successful, triggers a sound.

int __thiscall Player::checkObjectiveTrigger(int this, int triggerId)
{
    char resultFlag;
    int listPointer;
    int componentPtr;
    int nodeBase;
    undefined4 soundHandle;
    int tempSlot; // placeholder for stack manipulation
    int *listSlotPtr;
    int node;
    undefined4 audioDataSize;
    undefined4 audioFlags;

    // Temporary buffer for virtual function call (likely a transform/position)
    char transformBuffer[12];
    undefined4 transformExt1 = 0;
    undefined4 transformExt2 = 0;
    undefined4 transformExt3 = 0;
    undefined4 transformExt4 = _DAT_00d5780c; // global initialization constant

    // Get parent of sub-object at this+0x50 (sub-object is at offset 0x48)
    if (*(int *)(this + 0x50) == 0) {
        listPointer = 0;
    }
    else {
        listPointer = *(int *)(this + 0x50) - 0x48;
    }

    // Call virtual function 0x90 on that parent to fill transformBuffer
    (**(code **)(*listPointer + 0x90))(transformBuffer);

    // Get the container object (this+0x58) and its list slot at +0x1e90
    componentPtr = *(int *)(this + 0x58);
    listSlotPtr = (int *)(componentPtr + 0x1e90);

    // Determine the current node in the list (if any) to compare
    if (*listSlotPtr == 0) {
        node = 0;
    }
    else {
        node = *listSlotPtr - 0x48; // back to base
    }

    // Base of the sub-object we want to insert (from this+0x50)
    if (*(int *)(this + 0x50) == 0) {
        nodeBase = 0;
    }
    else {
        nodeBase = *(int *)(this + 0x50) - 0x48;
    }

    // Convert nodeBase to actual node pointer (add offset 0x48)
    int newNode = 0;
    if (nodeBase != 0) {
        newNode = nodeBase + 0x48;
    }

    // Insert/replace the node in the intrusive linked list
    if (*listSlotPtr != newNode) {
        if (*listSlotPtr != 0) {
            FUN_004daf90(listSlotPtr); // remove old node
        }
        *listSlotPtr = newNode;
        if (newNode != 0) {
            *(undefined4 *)(componentPtr + 0x1e94) = *(undefined4 *)(newNode + 4);
            *(int **)(newNode + 4) = listSlotPtr;
        }
    }

    // Query a target object from the container
    int targetObj = FUN_009a76f0(*(undefined4 *)(this + 0x58), &tempSlot, &tempSlot, 0);

    // Re-evaluate the list for consistency (second insertion block)
    int container2 = *(int *)(this + 0x58); // same as before? Actually unaff_ESI is likely the same 'this'
    listSlotPtr = (int *)(container2 + 0x1e90);
    if (node == 0) {
        node = 0;
    }
    else {
        node = node + 0x48; // convert back to raw pointer
    }
    if (*listSlotPtr != node) {
        if (*listSlotPtr != 0) {
            FUN_004daf90(listSlotPtr);
        }
        *listSlotPtr = node;
        if (node != 0) {
            *(undefined4 *)(container2 + 0x1e94) = *(undefined4 *)(node + 4);
            *(int **)(node + 4) = listSlotPtr;
        }
    }

    // Check the target object
    if ((targetObj != 0) && (*(int *)(targetObj + 0x24) != 0) && (*(int *)(targetObj + 0x24) != 0x48)) {
        // Get the base object of the sub-object at targetObj+0x24
        int subBase;
        if (*(int *)(targetObj + 0x24) == 0) {
            subBase = 0;
        }
        else {
            subBase = *(int *)(targetObj + 0x24) - 0x48;
        }

        // Virtual call 0x10 to compare hash
        resultFlag = (**(code **)(*subBase + 0x10))(0x55859efa, &tempSlot);

        if ((resultFlag != '\0') && (triggerId + 4 != 0)) {
            // Virtual call on global manager (audio system) at offset 0x1bc
            resultFlag = (**(code **)(vtableGlobal + 0x1bc))();
            if (resultFlag != '\0') {
                audioFlags = 0;
                soundHandle = FUN_006fbc40(0, 0);
                FUN_007f96a0(0x84e5bd0, 0x94, soundHandle, audioFlags);
                FUN_006fbc70();
                return triggerId + 4;
            }
        }
    }
    return 0;
}