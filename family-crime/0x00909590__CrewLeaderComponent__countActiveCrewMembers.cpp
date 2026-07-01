// FUNC_NAME: CrewLeaderComponent::countActiveCrewMembers
int CrewLeaderComponent::countActiveCrewMembers() const
{
    int count = 0;

    // Slot 0: offset +0x70
    if ((*(int*)(this + 0x70) != 0) && (*(int*)(this + 0x70) != 0x48)) {
        count++;
    }
    // Slot 1: offset +0x78
    if ((*(int*)(this + 0x78) != 0) && (*(int*)(this + 0x78) != 0x48)) {
        count++;
    }
    // Slot 2: offset +0x80
    if ((*(int*)(this + 0x80) != 0) && (*(int*)(this + 0x80) != 0x48)) {
        count++;
    }
    // Slot 3: offset +0x88
    if ((*(int*)(this + 0x88) != 0) && (*(int*)(this + 0x88) != 0x48)) {
        count++;
    }
    // Slot 4: offset +0x90
    if ((*(int*)(this + 0x90) != 0) && (*(int*)(this + 0x90) != 0x48)) {
        count++;
    }
    // Slot 5: offset +0x98
    if ((*(int*)(this + 0x98) != 0) && (*(int*)(this + 0x98) != 0x48)) {
        count++;
    }

    return count;
}