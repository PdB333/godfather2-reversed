// FUNC_NAME: FamilyManager::findCrewMemberIndex
int FamilyManager::findCrewMemberIndex(void) {
    int searchID = getCurrentCrewID(); // FUN_004dafd0 - returns the family/crew ID to search for
    CrewContainer* container = *(CrewContainer**)(*(int*)(this + 0x70) + 0x40); // m_pCrewData->crewContainers array
    int entryCount = *(int*)((int)container + *(short*)(this + 0x74) * 8); // count of entries in the current crew slot (selected by m_currentCrewSlotIndex)
    int* entryPtr = *(int**)((int)container + *(short*)(this + 0x74) * 8 + 4); // pointer to array of 0xC-byte crew member records

    for (int i = 0; i < entryCount; i++) {
        if (entryPtr[0] == searchID) {
            return i; // found at index i
        }
        entryPtr += 3; // skip to next record (each record is 12 bytes = 3 ints)
    }
    return -1; // not found
}