// FUNC_NAME: CrewLeaderComponent::assignCrewMemberToGangster
undefined4 __thiscall CrewLeaderComponent::assignCrewMemberToGangster(int this, int gangster)
{
    char isValid;
    int slotContentId;
    int unkValue; // from EBX (preserved register, likely some context pointer)
    uint unkIndex; // from stack local (possibly index or timestamp)
    int *slotPtr;
    uint slotIndex;
    uint uStack_14;
    undefined4 crewInfo[2]; // 8-byte structure passed to virtual functions
    
    slotIndex = 0;
    uStack_14 = (uint)(uint3)uStack_14; // truncation artifact, probably reading uninitialized stack
    if (gangster == 0) {
        return 0;
    }
    
    crewInfo[0] = 0;
    crewInfo[1] = 0;
    slotPtr = this + 0x293; // array of 4 crew slot entries at offset 0xA4C (each 4 bytes)
    
    do {
        if (*slotPtr != 0) {
            // Get some identifier from the current slot content (function called with no visible argument)
            slotContentId = FUN_00791300();
            if (slotContentId == gangster) {
                // Virtual call: fill crewInfo for this slot index (vtable entry at +0x218)
                (**(code **)(*this + 0x218))(slotIndex, crewInfo);
                
                isValid = FUN_00543270(crewInfo); // check if crew info is valid
                if (isValid != 0) {
                    // Virtual call: apply crew info to the gangster (vtable entry at +0x210)
                    (**(code **)(*this + 0x210))(gangster, crewInfo);
                    
                    // Write additional data into the gangster object
                    *(int *)(gangster + 0x860) = unkValue;  // +0x860: some field (e.g., crewLeader pointer)
                    *(uint *)(gangster + 0x864) = uStack_14; // +0x864: some field (e.g., slot index or timestamp)
                    return 1;
                }
            }
        }
        slotIndex++;
        slotPtr++;
    } while (slotIndex < 4);
    
    return 0;
}