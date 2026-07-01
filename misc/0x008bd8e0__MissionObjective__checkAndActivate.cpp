// FUNC_NAME: MissionObjective::checkAndActivate
// Function address: 0x008bd8e0
// Role: Checks if this mission objective's type field (+0x04) is 6 (active/ready state)
//       and if so, deactivates the current objective and activates a new stage via MissionManager.

bool MissionObjective::checkAndActivate()
{
    bool result = false;

    // Ensure this is a valid object and its type identifier at offset +0x04 is 6
    if (this != nullptr && *(int *)((char *)this + 4) == 6)
    {
        // Deactivate current objective (index 0)
        MissionManager::deactivateObjective(0);
        // Activate new objective with stage 1, sub‑stage 0
        MissionManager::activateObjective(1, 0);
        result = true;
    }

    return result;
}