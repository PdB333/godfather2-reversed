// FUNC_NAME: NetSession::sendGameEvent
// Function address: 0x00883670
// Role: Sends a game event (likely for network replication or dispatch)
// Parameters:
//   dataObj - object containing event data (+0x4 may be a string or buffer pointer)
//   unused - not used
//   objWithVtable - object with vtable at offset 0 containing method pointers; methods at +0x1ec and +0xa4 are used
bool NetSession::sendGameEvent(int dataObj, undefined4 unused, int* objWithVtable)
{
    int tempInt;          // iStack_38
    undefined4* tempPtr;  // puStack_34
    int local_24[4];      // local_24 likely used as output parameter for FUN_0054ebf0
    char local_28;        // local_28 as input buffer? Actually used with &local_28 in vtable call
    char auStack_14[20];  // temporary buffer for copying data from dataObj+4

    // Set up pointer chain: puStack_34 points to local_28's address
    tempPtr = (undefined4*)&local_28;
    local_24[0] = 0;

    // Call cleanup/reset method on objWithVtable (vtable+0x1ec)
    (**(code**)(*objWithVtable + 0x1ec))();

    // Copy data from dataObj+4 into auStack_14 via vtable method
    (**(code**)(*objWithVtable + 0xa4))(auStack_14, dataObj + 4);

    // Another copy operation: from tempPtr (which points to local_28) into local_28? 
    // Actually it copies from &tempPtr (i.e., &puStack_34) to &local_28? The second argument is &puStack_34
    (**(code**)(*objWithVtable + 0xa4))(&local_28, &tempPtr);

    // Acquire two resource/sequence numbers from a generator
    tempInt = FUN_0043b490();  // likely getNextSequence() or allocateResource()
    tempPtr = (undefined4*)FUN_0043b490();

    // Dispatch the event: pass local_24 (output), stack buffer, flags, and other parameters
    // Constants: 0x40122 (event type?), 0x1ff0000 (mask?), 2 (priority?), 0,0,0
    char cVar1 = FUN_0054ebf0(local_24, &stack0xffffffd0, 0x40122, 0x1ff0000, &tempInt, 2, 0, 0, 0);

    // Return true if event was successfully queued (cVar1 == 0)
    return cVar1 == '\0';
}