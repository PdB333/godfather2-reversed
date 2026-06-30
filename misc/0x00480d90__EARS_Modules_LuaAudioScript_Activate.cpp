// Xbox PDB: EARS::Modules::LuaAudioScript::Activate
// FUNC_NAME: GUIDManager::registerGUIDSerialization
uint GUIDManager::registerGUIDSerialization(void)
{
    uint *guidListHead; // [this+0x78]
    int *bufferPtr;     // temporary pointer into buffer
    int globalBase;     // from DAT_012233f4
    uint newGUID;
    uint currentGUID;
    undefined4 *bufferWrite; // write pointer into output buffer
    undefined4 *tempPtr;
    int esi = (int)this; // unaff_ESI represents 'this'

    globalBase = (int)DAT_012233f4;

    // +0x64 (100) is some pointer/flag, +0x68, +0x6c, +0x70 are other flags
    // If all are zero, skip registration and return aligned address
    if ((((*(int*)(esi + 100) == 0) && (*(int*)(esi + 0x68) == 0)) &&
         (*(int*)(esi + 0x6c) == 0)) && (*(int*)(esi + 0x70) == 0))
    {
        return (uint)(esi + 100) & 0xFFFFFF00;
    }

    guidListHead = (uint*)(esi + 0x78); // pointer to singly linked list head
    if (*(int*)(esi + 0x78) == 0)
    {
        // Allocate a new GUID from pool
        newGUID = FUN_004211e0((uint)(esi + 100)); // allocateGUID
        currentGUID = newGUID;
        if (*guidListHead != newGUID)
        {
            if (*guidListHead != 0)
            {
                // Remove old head from list
                currentGUID = FUN_004daf90(guidListHead); // removeGUIDFromList
            }
            *guidListHead = newGUID;
            if (newGUID != 0)
            {
                // Link the new GUID into the list
                currentGUID = *(uint*)(newGUID + 4);
                *(uint*)(esi + 0x7c) = currentGUID; // store next pointer
                *(uint**)(newGUID + 4) = guidListHead; // set prev? (or list head pointer)
            }
        }
        // Store a buffer pointer from global state
        *(undefined4*)(esi + 0x80) = *(undefined4*)(globalBase + 0x18);
        if (*guidListHead == 0) goto LAB_00480f22;
    }

    // Serialize GUID registration into the buffer
    // Write a type tag (2) and pointer to this object
    int bufferIndex = *(int*)(esi + 0x80);
    undefined4 *writePtr = *(undefined4**)(bufferIndex + 8);
    *writePtr = 2;                       // type marker for GUID registration?
    writePtr[1] = (undefined4)esi;       // pointer to this object
    int *sizePtr = (int*)(bufferIndex + 8);
    *sizePtr = *sizePtr + 8;             // advance buffer write position

    // Write the string "gGUID" into the buffer (type identifier)
    FUN_00625ca0(*(undefined4*)(esi + 0x80), "gGUID");

    // Shift some data in the buffer (probably to make room for header)
    int bufIdx2 = *(int*)(esi + 0x80);
    undefined4 *bufWrite2 = *(undefined4**)(bufIdx2 + 8);
    for (tempPtr = bufWrite2; bufWrite2 + (-4) < tempPtr; tempPtr = tempPtr + (-2))
    {
        *tempPtr = tempPtr[-2];
        tempPtr[1] = tempPtr[-1];
    }
    undefined4 *bufHead = *(undefined4**)(bufIdx2 + 8);
    bufWrite2[-4] = *bufHead;
    bufWrite2[-3] = bufHead[1];

    // Call a buffer copy/finalize routine (memmove + trim)
    int bufIdx3 = *(int*)(esi + 0x80);
    FUN_00633d60(bufIdx3 + 0x40,
                 *(int*)(bufIdx3 + 8) + (-0x10),
                 *(int*)(bufIdx3 + 8) + (-8));
    *(int*)(bufIdx3 + 8) = *(int*)(bufIdx3 + 8) + (-0x10);

    // Call a notify callback
    FUN_004cb0c0(0); // onGUIDRegistrationComplete

    // Write another tag (2) with null object pointer (maybe end marker)
    int bufIdx4 = *(int*)(esi + 0x80);
    undefined4 *bufWrite3 = *(undefined4**)(bufIdx4 + 8);
    *bufWrite3 = 2;
    bufWrite3[1] = 0;
    int *sizePtr2 = (int*)(bufIdx4 + 8);
    *sizePtr2 = *sizePtr2 + 8;

    // Write "gGUID" again (or confirm type)
    FUN_00625ca0(*(undefined4*)(esi + 0x80), "gGUID");

    // Shift and copy again
    int bufIdx5 = *(int*)(esi + 0x80);
    undefined4 *bufWrite4 = *(undefined4**)(bufIdx5 + 8);
    for (tempPtr = bufWrite4; bufWrite4 + (-4) < tempPtr; tempPtr = tempPtr + (-2))
    {
        *tempPtr = tempPtr[-2];
        tempPtr[1] = tempPtr[-1];
    }
    undefined4 *bufHead2 = *(undefined4**)(bufIdx5 + 8);
    bufWrite4[-4] = *bufHead2;
    bufWrite4[-3] = bufHead2[1];

    // Finalize buffer
    int bufIdx6 = *(int*)(esi + 0x80);
    FUN_00633d60(bufIdx6 + 0x40,
                 *(int*)(bufIdx6 + 8) + (-0x10),
                 *(int*)(bufIdx6 + 8) + (-8));
    *(int*)(bufIdx6 + 8) = *(int*)(bufIdx6 + 8) + (-0x10);

    // Execute "startup" function (call by name)
    uint retVal = FUN_00468f40("startup");

LAB_00480f22:
    return retVal & 0xFFFFFF00;
}