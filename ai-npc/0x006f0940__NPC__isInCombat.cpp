// FUNC_NAME: NPC::isInCombat
// Function at 0x006f0940: Checks if the NPC is in combat-related states (2 or 3)
// Offset 0x20: current state enum (0=idle,1=patrol,2=combat,3=flee)

bool NPC::isInCombat() const
{
    // Switch on the state field at +0x20
    switch (*(int *)(this + 0x20))
    {
    case 0:  // Idle
    case 1:  // Patrolling
        return false;
    case 2:  // InCombat
    case 3:  // Fleeing
        return true;
    default:
        return false; // safety fallback
    }
}