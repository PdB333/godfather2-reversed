// FUNC_NAME: CrewLeaderComponent::getCrewMemberAtIndex
uint32_t __thiscall CrewLeaderComponent::getCrewMemberAtIndex(int index) {
    // Offset 0x7C: array of crew member pointers (4 bytes each)
    return *(uint32_t*)(this + 0x7C + index * 4);
}