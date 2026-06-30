// FUNC_NAME: CrewLeaderComponent::removeCrewMember
// Address: 0x006b2e00
// Removes a crew member ID from the primary list. If not found and secondary list is inactive, attempts to add to secondary list.

void __thiscall CrewLeaderComponent::removeCrewMember(int memberId)
{
    // +0xb4 = pointer to array of member IDs
    // +0xb8 = count of members
    // +0xfc = flag: 0 means secondary list is inactive
    uint memberCount = *(uint *)(this + 0xb8);
    uint index = 0;

    if (memberCount != 0)
    {
        int *pMemberArray = *(int **)(this + 0xb4);
        do
        {
            if (*pMemberArray == memberId)
            {
                // Redundant check, always true
                if (-1 < (int)index)
                {
                    if (index != memberCount - 1)
                    {
                        // Swap last element into removed slot
                        int *arrayBase = *(int **)(this + 0xb4);
                        arrayBase[index] = arrayBase[memberCount - 1];
                    }
                    // Decrement count
                    *(int *)(this + 0xb8) = memberCount - 1;
                    // Notify and reindex
                    sub_790110(0);
                    sub_791350(this);
                }
                return;
            }
            index++;
            pMemberArray++;
        } while (index < memberCount);
    }

    // If not found and secondary list is inactive, try secondary list
    if (*(int *)(this + 0xfc) == 0)
    {
        int secondaryResult = sub_7915b0();
        if (secondaryResult != 0)
        {
            sub_8c2ab0(this, memberId);
        }
    }
}