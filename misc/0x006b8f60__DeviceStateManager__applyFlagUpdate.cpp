// FUNC_NAME: DeviceStateManager::applyFlagUpdate

void __thiscall DeviceStateManager::applyFlagUpdate(DeviceState* targetState)
{
    uint setFlags = *(uint *)(this + 0x88);   // +0x88: bitmask of flags to set
    uint clearFlags = *(uint *)(this + 0x8c); // +0x8c: bitmask of flags to clear

    // --- Process set flags ---
    if ((setFlags & 1) != 0) {
        this->enableDevice();  // bit 0: enable device
    }
    if ((setFlags & 4) != 0) {
        this->setDeviceMode(1);  // bit 2: set mode to active (1)
    }
    if ((setFlags & 0x10) != 0) {
        targetState->stateFlags |= 0x10; // +0x34: bit 4
    }
    if ((setFlags & 0x20) != 0) {
        targetState->stateFlags |= 0x20; // bit 5
    }
    if ((setFlags & 0x40) != 0) {
        targetState->stateFlags |= 0x40; // bit 6
    }
    if ((int8_t)setFlags < 0) { // bit 7
        targetState->stateFlags |= 0x80;
    }
    if ((setFlags & 0x100) != 0) {
        targetState->stateFlags |= 0x100; // bit 8
    }
    if ((setFlags & 0x200) != 0) {
        targetState->stateFlags |= 0x200; // bit 9
    }
    if ((setFlags & 0x400) != 0) {
        targetState->stateFlags |= 0x400; // bit 10
    }
    if ((setFlags & 0x800) != 0) {
        targetState->stateFlags |= 0x800; // bit 11
    }
    if ((setFlags & 8) != 0) {
        targetState->stateFlags |= 8; // bit 3
    }

    // --- Process clear flags ---
    if ((clearFlags & 1) != 0) {
        this->disableDevice(); // bit 0: disable device
    }
    if ((clearFlags & 4) != 0) {
        this->setDeviceMode(0); // bit 2: set mode to inactive (0)
    }
    if ((clearFlags & 0x10) != 0) {
        targetState->stateFlags &= ~0x10;
    }
    if ((clearFlags & 0x20) != 0) {
        targetState->stateFlags &= ~0x20;
    }
    if ((clearFlags & 0x40) != 0) {
        targetState->stateFlags &= ~0x40;
    }
    if ((int8_t)clearFlags < 0) { // bit 7
        targetState->stateFlags &= ~0x80;
    }
    if ((clearFlags & 0x100) != 0) {
        targetState->stateFlags &= ~0x100;
    }
    if ((clearFlags & 0x200) != 0) {
        targetState->stateFlags &= ~0x200;
    }
    if ((clearFlags & 0x400) != 0) {
        targetState->stateFlags &= ~0x400;
    }
    if ((clearFlags & 0x800) != 0) {
        targetState->stateFlags &= ~0x800;
    }
    if ((clearFlags & 8) != 0) {
        targetState->stateFlags &= ~8;
    }
}