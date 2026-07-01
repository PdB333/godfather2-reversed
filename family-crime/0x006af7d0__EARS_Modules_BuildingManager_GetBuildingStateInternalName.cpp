// Xbox PDB: EARS::Modules::BuildingManager::GetBuildingStateInternalName
// FUNC_NAME: Building::stateToString
// Address: 0x006af7d0
// Converts building state enum to display string.
char* Building::stateToString(int state)
{
    switch (state)
    {
    case 0:
        return "Open";
    case 1:
        return "Closed";
    case 2:
        return "Repairing";
    case 3:
        return "Smoldering";
    case 4:
        return "Burning";
    default:
        return "Unknown";
    }
}