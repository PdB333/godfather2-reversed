// FUNC_NAME: Entity::isTargetable (thunk to FUN_006b4860)
bool Entity::isTargetable() {
    // Check if this entity can be targeted/interacted with
    bool overrideTargetable = *(bool *)(this + 0x16c); // +0x16c: targetable override flag

    uint flags = *(uint *)(this + 0x34); // +0x34: entity flags (bit 0 = disabled?, bits 0x120000 = something)
    if ((flags & 0x120000) == 0 && (flags & 1) == 0) {
        int componentPtr = *(int *)(this + 0x40); // +0x40: pointer to some component (e.g., health/state component)
        if (componentPtr != 0) {
            int component = FUN_008c74d0(componentPtr); // likely a virtual function to get state
            if (component != 0) {
                uint stateFlags = *(uint *)(component + 0x84); // +0x84: state flags (bit 5 = dead/inactive?)
                // Check if bit 5 is clear (meaning not dead/inactive)
                if ((~((byte)(stateFlags >> 5) & 1) & 1) != 0) {
                    return overrideTargetable;
                }
            }
        }
    }
    return true; // default to targetable if conditions fail
}