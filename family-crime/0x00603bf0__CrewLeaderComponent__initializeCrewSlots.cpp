// FUNC_NAME: CrewLeaderComponent::initializeCrewSlots
// Offset +0x4c: bitfield flags (bit3 = crewSlotsInitialized)
void CrewLeaderComponent::initializeCrewSlots() {
    // Check if crew slots have already been initialized
    if (!(*(uint*)(this + 0x4c) & 0x08)) {
        // Initialize each of the 5 crew member slots
        initializeCrewSlot(); // Called 5 times, each likely sets up one slot
        initializeCrewSlot();
        initializeCrewSlot();
        initializeCrewSlot();
        initializeCrewSlot();
        // Mark crew slots as initialized
        *(uint*)(this + 0x4c) |= 0x08;
    }
}