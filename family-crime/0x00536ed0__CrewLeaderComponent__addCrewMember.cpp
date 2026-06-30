//FUNC_NAME: CrewLeaderComponent::addCrewMember
int __thiscall CrewLeaderComponent::addCrewMember(int memberId, unsigned short* insertionOrder) {
    // this+0x70: pointer to crew data array descriptor
    // this+0x76: current crew index (short)
    short currentIndex;
    int crewDataDesc;
    int entryPtr;
    int newNode;
    unsigned short localIndices[64];
    unsigned short* indices;
    int count;
    unsigned int dummy; // local_8c, used as placeholder for null param_2

    crewDataDesc = *(int*)(this + 0x70);
    // Validate crew data descriptor: non-null, count > 0, array pointer non-null, current index in range
    if ((crewDataDesc == 0) ||
        (*(int*)(crewDataDesc + 0x18) < 1) ||
        (*(int*)(crewDataDesc + 0x1c) == 0) ||
        ((currentIndex = *(short*)(this + 0x76), currentIndex < 0) ||
         (*(int*)(crewDataDesc + 0x18) <= (int)currentIndex))) {
        entryPtr = 0;
    } else {
        // Entry size = 0x18 bytes
        entryPtr = *(int*)(crewDataDesc + 0x1c) + currentIndex * 0x18;
    }

    newNode = allocateNode(); // FUN_00536d50
    if (newNode != 0) {
        if (memberId < 0) {
            memberId = 0;
        }
        *(int*)(newNode + 4) = this; // Store backpointer to this crew leader

        if (insertionOrder == (unsigned short*)0x0) {
            // Build default sequential insertion order
            indices = localIndices;
            count = *(int*)(entryPtr + 8); // +0x08: number of existing members in this entry
            dummy = 0;
            if (count > 0x3f) {
                count = 0x40; // Cap at 64
            }
            for (int i = 0; i < count; i++) {
                localIndices[i] = (unsigned short)i;
            }
            insertionOrder = &dummy; // Use dummy pointer (will be ignored by sortIndices? Actually it's passed to insertIntoSortedList)
        } else {
            insertionOrder[1] = (unsigned int)localIndices; // Store local array pointer in param_2[1] (offset 4)
            sortIndices(insertionOrder); // FUN_00536c60
        }
        insertIntoSortedList(entryPtr, memberId, memberId, insertionOrder); // FUN_00536e00
        return newNode;
    }
    return 0;
}