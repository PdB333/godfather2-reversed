// FUNC_NAME: NPCCrewComponent::countActiveCrewMembers
int __fastcall NPCCrewComponent::countActiveCrewMembers(int this) {
    int count = 0;
    int numMembers = *(int *)(this + 0x1a8); // +0x1a8: number of crew members in array
    if (numMembers != 0) {
        int **memberArray = *(int ***)(this + 0x1a4); // +0x1a4: pointer to array of crew member pointers
        do {
            // Check if member is active (bit 0 of byte at offset 0x5f in member's data)
            if ((*(byte *)(*(int *)(*memberArray + 8) + 0x5f) & 1) != 0) {
                count++;
            }
            memberArray++;
            numMembers--;
        } while (numMembers != 0);
    }
    return count;
}