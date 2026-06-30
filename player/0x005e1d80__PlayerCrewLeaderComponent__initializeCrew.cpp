// FUNC_NAME: PlayerCrewLeaderComponent::initializeCrew
// Address: 0x005e1d80

bool __thiscall PlayerCrewLeaderComponent::initializeCrew() {
    // +0x1744: byte flag, non-zero if already initialized
    if (*(char *)(this + 0x1744) != '\0') {
        return false;
    }

    // Array of 5 crew slots starting at this+4, each 0x4a4 bytes
    int slotBase = this + 4;
    for (int i = 0; i < 5; i++) {
        int slot = slotBase + i * 0x4a4;
        // +0x488: slot index/ID
        *(int *)(slot + 0x488) = i;
        // Initialize the slot (call to 0x005e8300)
        initCrewSlot(slot);
        // Global initialization call (0x005e8510)
        onCrewInit();
    }

    // +0x173c: some int counter or state
    *(int *)(this + 0x173c) = 0;

    // +0x1738: pointer to a previously allocated resource
    if (*(void **)(this + 0x1738) != nullptr) {
        // Release that resource (call to 0x009c8f10)
        releaseCrewResource(*(void **)(this + 0x1738));
        *(void **)(this + 0x1738) = nullptr;
    }

    // +0x1740: another state variable (maybe related to the resource)
    *(int *)(this + 0x1740) = 0;

    // Mark as initialized
    *(char *)(this + 0x1744) = 1;

    return true;
}