// FUNC_NAME: PlayerCrewLeaderComponent::resetCrewSlots
void __thiscall PlayerCrewLeaderComponent::resetCrewSlots(PlayerCrewLeaderComponent* this) {
    int isReady;
    int slotIndex;

    // Global system initialization (may be a static manager method)
    initializeSystem();

    // Check if the crew subsystem (e.g., CSACrewComponent) is initialized
    // this->m_pCrewSystem is at +0xf0, virtual function isInitialized() at vtable+0x254
    isReady = (*(int (__thiscall**)(void*))(*(int**)(*(int*)((char*)this + 0xf0)) + 0x254))();

    if (isReady != 0) {
        // Reset each of the 6 crew slots (player crew has up to 6 members)
        for (slotIndex = 0; slotIndex < 6; slotIndex++) {
            resetCrewSlot(slotIndex, 0);  // clear slot with flag=0
        }
    }
}