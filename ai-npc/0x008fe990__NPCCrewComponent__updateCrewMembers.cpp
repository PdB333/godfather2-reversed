// FUNC_NAME: NPCCrewComponent::updateCrewMembers
void __fastcall NPCCrewComponent::updateCrewMembers(NPCCrewComponent* this)
{
    // Crew array starts at this+0x78, 3 entries, each 8 bytes (pointer + unknown int)
    // Use 1-based index to identify each crew slot
    for (uint i = 0; i < 3; i++)
    {
        int* crewPtr = reinterpret_cast<int*>(this->crewArray[i].ptr); // offset +0x78 + i*8
        if (crewPtr != nullptr)
        {
            // Process the active crew member (index i+1)
            processCrewMember(i + 1);
        }
    }
}