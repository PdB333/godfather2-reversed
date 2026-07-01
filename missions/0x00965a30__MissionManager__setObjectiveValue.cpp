// FUNC_NAME: MissionManager::setObjectiveValue
// Function address: 0x00965a30
// Sets a parameter value for a mission objective identified by ID.
// This function iterates through the mission objectives array and updates
// the value field for the matching objective, then clears the current objective
// index and sets a flag indicating a change.

void __thiscall MissionManager::setObjectiveValue(uint objectiveId, int newValue)
{
    // Global flag indicating game is active (e.g., not in menus)
    if (!g_isGameRunning)
        return;

    // Check if this manager's flags have bit 0 set; if so, abort
    if ((this->flags & 0x01) != 0)
        return;

    // If no objectives are defined, nothing to do
    if (this->objectiveCount == 0)
        return;

    // Iterate over the list of mission objective pointers
    uint index = 0;
    while (true) {
        // Each objective object has an ID field at offset 0x5C
        int currentId = this->objectiveList[index]->id;
        if (currentId == objectiveId)
            break;

        index++;
        if (index >= this->objectiveCount)
            return; // ID not found
    }

    // Retrieve the objective object pointer from the list
    MissionObjective* objective = this->objectiveList[index];
    if (objective != NULL) {
        // Set the parameter value at offset 0x10
        objective->value = newValue;

        // Clear the current objective index (offset 0xC4)
        this->currentObjectiveIndex = 0;

        // Set bit 2 of flags (offset 0x6F4) to indicate objective update
        this->flags |= 0x04;
    }
}