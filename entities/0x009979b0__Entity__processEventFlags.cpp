// FUNC_NAME: Entity::processEventFlags
// Function address: 0x009979b0
// Role: Handles state flags for entity activation/notification.

void __thiscall Entity::processEventFlags(int param) {
    uint flags;
    uint *linkedFlags;
    
    // Check if bit 1 of stateFlags is set (activation event pending)
    if (((this->stateFlags >> 1) & 1) != 0) {
        this->onActivationEvent();
        if (param == 1) {
            // Set bit 4 on linked object's flags at offset +0x184 (mark for update)
            linkedFlags = (uint *)(*(int *)(this->linkedObject) + 0x184);
            *linkedFlags |= 0x10;
        }
    }
    // Check if bit 4 of stateFlags is set (deactivation event pending)
    if ((this->stateFlags & 0x10) != 0) {
        // Call deactivation handler, passing a pointer to this object
        this->onDeactivationEvent((int*)&this);
    }
    // Clear bit 4 of stateFlags
    this->stateFlags &= 0xFFFFFFEF;
}