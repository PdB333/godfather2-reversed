// FUNC_NAME: CrewLeaderComponent::areAllCrewMembersIdle
// Function at 0x009650e0: checks if all crew members have a specific flag (byte at offset 0x59) set to 0
// Returns true if all members have flag == 0, false otherwise
bool __thiscall CrewLeaderComponent::areAllCrewMembersIdle(CrewLeaderComponent *this) {
    uint index = 0;                // loop index
    bool result = true;            // default to true (all idle)

    // If there are any crew members in the list (count at +0x33c is non-zero)
    if (*(uint *)((char *)this + 0x33c) != 0) {
        int **currentPointer = *(int ***)((char *)this + 0x338);  // pointer to array of crew member pointers

        // Loop through all crew members
        while (*(char *)(*currentPointer + 0x59) == '\0') {  // check byte at +0x59 of the crew member object
            index++;
            currentPointer++;  // advance to next pointer in array

            // If we've checked all members, return true
            if (*(uint *)((char *)this + 0x33c) <= index) {
                return result;  // true
            }
        }
        // If we exit the while loop, a crew member had non-zero flag -> not idle
        result = false;
    }
    return result;  // false if any member is busy, true otherwise
}