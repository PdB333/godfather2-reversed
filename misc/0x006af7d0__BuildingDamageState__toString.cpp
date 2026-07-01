// FUNC_NAME: BuildingDamageState::toString
char* BuildingDamageState::toString(BuildingDamageState state)
{
  switch(state) {
  case 0: // Open
    return "Open";
  case 1: // Closed
    return "Closed";
  case 2: // Repairing
    return "Repairing";
  case 3: // Smoldering
    return "Smoldering";
  case 4: // Burning
    return "Burning";
  default:
    return "Unknown";
  }
}