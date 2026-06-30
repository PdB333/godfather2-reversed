// FUNC_NAME: setMissionState
// Sets a mission state for a given mission ID. Returns 1 on success, 0 on failure.
// param_1: missionId (full 32-bit ID, low 16 bits used for indexing)
// param_2: newState (new state value to assign)

undefined1 setMissionState(uint missionId, int newState)
{
    uint index;             // uVar3
    MissionEntry *missionEntry;  // iVar1
    MissionStateEntry *stateEntry; // piVar4
    void *obj;             // from piVar4[2]

    // Extract low 16 bits as index, must be < 0x200 (max 512 entries)
    index = missionId & 0xffff;
    if (index >= 0x200) {
        return 0;
    }

    // Compute pointer to mission entry in the first table
    // The table starts at gMissionManagerBase + 0x10, each entry 0x30 bytes
    missionEntry = (MissionEntry *)(index * 0x30 + 0x10 + gMissionManagerBase);
    if (missionEntry == (MissionEntry *)0x0) {
        return 0;
    }

    // Verify that the stored mission ID matches the requested one
    if (missionEntry->fullId != missionId) {
        return 0;
    }

    // Check that the secondary table pointer exists
    if (*(int *)(gMissionManagerBase + 0x603c) == 0) {
        return 0;
    }

    // Compute pointer to state entry in second table (0x74 bytes each)
    stateEntry = (MissionStateEntry *)(index * 0x74 + *(int *)(gMissionManagerBase + 0x603c));
    if (stateEntry == (MissionStateEntry *)0x0) {
        return 0;
    }

    // Check that the state entry's first field (flags?) is non-zero
    if (stateEntry->flags == 0) {
        return 0;
    }

    // Set the new state at offset 0x64 (piVar4[0x19])
    stateEntry->state = newState;

    // If there is a linked object at offset 0x08, update it too
    obj = stateEntry->linkedObject;
    if (obj != (void *)0x0) {
        // Set bit 1 at offset 0x4A (ushort)
        *(ushort *)((char *)obj + 0x4a) |= 2;
        // Set state at offset 0x54
        *(int *)((char *)obj + 0x54) = newState;
    }

    return 1;
}