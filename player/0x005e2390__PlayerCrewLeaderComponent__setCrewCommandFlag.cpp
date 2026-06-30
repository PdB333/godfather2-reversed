// FUNC_NAME: PlayerCrewLeaderComponent::setCrewCommandFlag
bool PlayerCrewLeaderComponent::setCrewCommandFlag(uint flagMask) {
    // Check if the player is a crew leader (+0x1744 = bIsCrewLeader)
    if (*(bool*)(this + 0x1744) != false) {
        // Retrieve the target crew member/entity (FUN_005e2150)
        void* target = FUN_005e2150(); // getTargetCrewMember()?
        if (target != nullptr) {
            // Set the command flags on the target (+0x250 = commandFlags)
            *(uint*)(target + 0x250) |= flagMask;
            return true;
        }
    }
    return false;
}