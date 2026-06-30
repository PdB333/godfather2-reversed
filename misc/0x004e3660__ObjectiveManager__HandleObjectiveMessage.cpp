// FUNC_NAME: ObjectiveManager::HandleObjectiveMessage

#include <cstdint>

// Global flag: set to 1 when an objective event is being processed
extern int g_bObjectiveActive;

// Forward declaration of the objective display function.
// This function likely shows a UI message or updates the objective tracker.
// The specific meanings of the argument tuples are unknown but may encode
// objective type, icon, priority, etc.
void DisplayObjectiveMessage(int a1, int a2 = 0, int a3 = 0, int a4 = 0, int a5 = 0);

void ObjectiveManager::HandleObjectiveMessage(int objectiveId)
{
    // Mark that an objective is currently active/being handled
    g_bObjectiveActive = 1;

    // Dispatch based on objective ID (0, 10, 1, 2 are known)
    if (objectiveId == 0)
    {
        DisplayObjectiveMessage(5, 2, 1, 1, 2);
    }
    else if (objectiveId == 10)
    {
        DisplayObjectiveMessage(2, 2, 1, 1, 2);
    }
    else if (objectiveId == 1)
    {
        DisplayObjectiveMessage(5, 6, 1, 2, 6);
    }
    else if (objectiveId == 2)
    {
        // Only one argument needed; rest default to 0
        DisplayObjectiveMessage(5);
    }
    // Other objective IDs are ignored
}