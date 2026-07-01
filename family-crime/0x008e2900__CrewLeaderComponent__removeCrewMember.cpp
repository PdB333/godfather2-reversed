// FUNC_NAME: CrewLeaderComponent::removeCrewMember
void __thiscall CrewLeaderComponent::removeCrewMember(int thisPtr, int memberId)
{
    char flag;
    int *slotPtr;
    int slotIndex;
    int slotBase;
    int memberData;
    undefined4 stackVar1;
    undefined1 *stackVar2;
    undefined1 stackVar3;
    undefined1 localArray[4];
    int refCount[2];

    // Check if crew is active (flag at +0x1A4)
    if (*(char *)(thisPtr + 0x1A4) == '\0') {
        return;
    }

    slotIndex = 0;
    slotBase = thisPtr + 0x88; // Start of crew slot array (3 slots, each 0x5C bytes)

    do {
        // Check if slot has a crew member pointer at +0x30
        if (*(int *)(slotBase + 0x30) != 0) {
            // Get the crew member object from the slot
            slotPtr = (int *)FUN_00446100(slotBase, 0); // Likely returns pointer to crew member data
            if (slotPtr != (int *)0x0) {
                memberData = 0;
                // Call virtual function at vtable+0x10 with hash to get member's ID structure
                char result = (**(code **)(*slotPtr + 0x10))(0x43c8ec5b, &memberData);
                if ((result != '\0') && (memberData != 0) && (*(int *)(memberData + 0x180) == memberId)) {
                    // Found matching member, clear the slot
                    FUN_0045ca00(thisPtr); // Likely resets slot state
                    // Get the pointer stored at slot's +0x30 (same as earlier)
                    stackVar1 = *(undefined4 *)(slotBase + 0x30);
                    stackVar2 = localArray;
                    stackVar3 = 0;
                    // Release the member object (decrement refcount)
                    FUN_00408a00(&stackVar1, 0);
                    if (refCount[0] == 0) {
                        return;
                    }
                    // Delete the member object if refcount reached zero
                    FUN_004daf90(refCount);
                    return;
                }
            }
        }
        slotIndex = slotIndex + 1;
        slotBase = slotBase + 0x5C;
        if (2 < slotIndex) {
            return;
        }
    } while( true );
}